program simulate
implicit none
!constants (m/s**2)
double precision, parameter :: g=9.80665
!timing variables (s)
double precision :: time=0, endtime=10, dt=.01
!mass (kg)
double precision :: m = 4
!state variables (velocity through air, flight path angle, heading angle, roll rate)
double precision :: vAir=1, gammaAir=0, psi=0, p=0
!more state variables
double precision :: theta=0, psidot=0, phi=0
!control variables
double precision :: throttle, aileron, Cl
!lift and drag
double precision :: L, D
!aircraft velocity [u,v,w] in FAA, aircraft reference frame
double precision, dimension(3) :: vinert = [0,0,0]
!moments of inertia
interface
	real(c_double) function getAileron() bind(c)
		!returns aileron from external c function
		use iso_c_binding
		implicit none
	end function
	real(c_double) function getThrottle() bind(c)
		!returns throttle from external c function
		use iso_c_binding
		implicit none
	end function
	real(c_double) function getLiftCoeff() bind(c)
		!returns commanded lift coefficient from external c function
		use iso_c_binding
		implicit none
	end function
end interface
do while (time<endtime)
throttle = getThrottle()
aileron = getAileron()
Cl = getLiftCoeff()
time = time + dt
L = lift(Cl, vAir)
D = drag(Cl, vAir)
vAir = vAir + ((throttle-D)/m-g*sin(gammaAir)) * dt
gammaAir = gammaAir + ( (L*cos(phi)-m*g*cos(gammaAir)) / (m*vAir) ) * dt
p = p + (rollDamp(p) + rollAileron(aileron)) * dt
psidot = ( L*sin(phi) / (m*vAir*cos(gammaAir)) ) 
phi = phi + (p + psidot * sin(theta))
end do
write(*,*) vAir
contains
double precision function rollAileron(aileron)
	implicit none
	!returns roll moment as a function of aileron deflection 
	double precision, intent(in) :: aileron 
	!constant of proportionality
	double precision :: kAileron = 1
	rollAileron = kAileron*aileron
end function
double precision function rollDamp(p)
	!returns damping moment as a function of roll rate
	implicit none
	double precision, intent(in) :: p
	!damping constant
	double precision :: damping = 1
	rollDamp = - damping * p
end function
double precision function lift(Cl, vAir)
	!returns lift as a function of Cl and velocity 
	implicit none
	double precision, intent(in) :: Cl, vAir
	double precision :: rho = 1.275 !kg/m**3
	lift = .5 * rho * vAir*vAir * Cl
end function
double precision function drag(Cl, vAir)
	!returns drag as a function of Cl and velocity 
	implicit none
	double precision, intent(in) :: Cl, vAir
	double precision :: rho = 1.275 !kg/m**3
	double precision :: Cd0=.02, k=.001
	drag = .5 * rho * vAir*vAir * (Cd0 + k * Cl**Cl)
end function
function inert2body(vector, rot)
	!returns vector in body-centered co-ordinates, given rotation as theta, phi, psi
	double precision, dimension(3) :: inert2body
	double precision, dimension(3) :: rot
	double precision, dimension(3) :: vector
	double precision, dimension(3,3) :: transform
	integer :: i,j
	double precision :: cosR, cosP, cosY, sinR, sinP, sinY
	cosR=cos(rot(1))
	cosP=cos(rot(2)) 
	cosY=cos(rot(3))
	sinR=sin(rot(1))
	sinP=sin(rot(2))
	sinY=sin(rot(3))
	transform = reshape( [cosP*cosY, -cosR*sinY+sinR*sinP*cosY, sinR*sinY+cosR*sinP*cosY, &
		cosP*sinY, cosR*cosY+sinR*sinP*sinY, -sinR*cosY+cosR*sinP*sinY, &
		-sinP, sinR*cosP, cosR*cosP], [3,3] )
	inert2body = matmul(transform, vector)
end function
function body2inert(vector, rot)
	!return transformed vector
	double precision, dimension(3) :: body2inert
	double precision, dimension(3) :: rot
	double precision, dimension(3) :: vector
	double precision, dimension(3,3) :: transform
	integer :: i,j
	double precision :: cosR, cosP, cosY, sinR, sinP, sinY
	cosR=cos(rot(1))
	cosP=cos(rot(2)) 
	cosY=cos(rot(3))
	sinR=sin(rot(1))
	sinP=sin(rot(2))
	sinY=sin(rot(3))
	transform = reshape( [cosP*cosY, cosP*sinY, -sinP, &
		-cosR*sinY+sinR*sinP*cosY, cosR*cosY+sinR*sinP*sinY, sinR*cosP, &
		sinR*sinY+cosR*sinP*cosY, -sinR*cosY+cosR*sinP*sinY, cosR*cosP], [3,3] )
	body2inert = matmul(transform, vector)
end function
end program simulate
