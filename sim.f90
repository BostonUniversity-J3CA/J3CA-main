program simulate
implicit none
!constants (m/s**2)
double precision, parameter :: g=9.80665
!timing variables (s)
double precision :: time=0, endtime=10, dt=.01
!mass (kg)
double precision :: m = 4
!control variables
double precision :: throttle, aileron, Cl
!lift and drag
double precision :: L, D
!aircraft velocity [u,v,w] in FAA, aircraft reference frame
double precision, dimension(3) :: vbody = [0,0,0]
!euler angles
double precision :: psi=0, phi=0, theta =0
!euler rates
double precision :: psidot=0, phidot=0, thetadot=0
!body angular velocities (roll, pitch, yaw)
double precision :: p, q, r
!gravity vector
double precision, dimension(3) :: gravity
!moments of inertia
double precision :: Ix=1, Iy=1, Iz=1, Ixz=1, Izx=1
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
gravity = inert2body([0d0,0d0,m*g],[psi,phi,theta])
!calculate forces
L = lift(Cl, vbody(1))
D = drag(Cl, vbody(1))
!calculate angular velocities from Euler rates
p = psidot-psidot*sin(theta)
q = thetadot*cos(phi)+psidot*cos(theta)*sin(phi)
r = psidot*cos(theta)*cos(phi)-thetadot*sin(phi)
!calculate acceleration, update veloctiy
vbody(1) = vbody(1)+((throttle-D+gravity(1))/m-q*vbody(3)+r*vbody(2))*dt
vbody(2) = vbody(2)+((gravity(2))/m-r*vbody(1)+p*vbody(3))*dt
vbody(3) = vbody(3)+((-L+gravity(3))/m-p*vbody(2)+q*vbody(1))*dt
!solve for pdot, qdot, rdot, update p, q, r
!update Euler rates
thetadot = q*cos(phi)-r*sin(phi)
phidot = p + q*sin(phi)*tan(theta) + r*cos(phi)*tan(theta)
psidot = (q*sin(phi) + r*cos(phi))/cos(theta)
!update Euler angles
theta = theta + thetadot*dt
phi = phi + phidot*dt
psi = psi + psidot*dt
end do
write(*,*) vbody
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
