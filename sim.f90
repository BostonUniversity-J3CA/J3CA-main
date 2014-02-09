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
!Forces (thrust, lift, and drag)
double precision :: T, L, D
!Moments (roll, pitch, yaw)
double precision :: mL, mM, mN
!aircraft velocity [u,v,w] in FAA, aircraft reference frame
double precision, dimension(3) :: vbody = [0,0,0]
!aircraft velocity, inertial reference frame
double precision, dimension(3) :: vinert = [0,0,0]
!euler angles
double precision :: psi=0, phi=0, theta =0
!euler rates
double precision :: psidot=0, phidot=0, thetadot=0
!body angular velocities (roll, pitch, yaw) and acceleration
double precision :: p, q, r, pdot, qdot, rdot
!gravity vector
double precision, dimension(3) :: gravity
!moments of inertia
double precision :: Ix=1, Iy=1, Iz=1, Ixz=1, Izx=1
!distance
double precision, dimension(3) :: distance = [0,0,0]
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
	double precision function rollAileron(aileron)
		double precision, intent(in) :: aileron
	end function
	double precision function rollDamp(p)
		double precision, intent(in) :: p
	end function
	double precision function lift(Cl, vAir)
		double precision, intent(in) :: Cl, vAir
	end function
	double precision function drag(Cl, vAir)
		double precision, intent(in) :: Cl, vAir
	end function
end interface
open(unit = 1, file = "sim.dat")
1001 format(f6.2,T10,f6.2,T20,f6.2,T30,f6.2,T40,f6.2,T50,f6.2)
do while (time<endtime)
time = time + dt
!calculate angular velocities from Euler rates
p = psidot-psidot*sin(theta)
q = thetadot*cos(phi)+psidot*cos(theta)*sin(phi)
r = psidot*cos(theta)*cos(phi)-thetadot*sin(phi)
!get control inputs (eventually will only happen at 50 Hz)
throttle = getThrottle()
aileron = getAileron()
Cl = getLiftCoeff()
!calculate forces
L = lift(Cl, vbody(1))
D = drag(Cl, vbody(1))
T = throttle
gravity = inert2body([0d0,0d0,m*g],[psi,phi,theta])
!calculate moments
mL = rollAileron(aileron)+rollDamp(p)
mM = 0
mN = 0
!calculate acceleration, update veloctiy
vbody(1) = vbody(1)+((throttle-D+gravity(1))/m-q*vbody(3)+r*vbody(2))*dt
vbody(2) = vbody(2)+((gravity(2))/m-r*vbody(1)+p*vbody(3))*dt
vbody(3) = vbody(3)+((-L+gravity(3))/m-p*vbody(2)+q*vbody(1))*dt
!solve for pdot, qdot, rdot, update p, q, r
pdot = (Ix*Ixz*p*q - Ixz**2*q*r - Ixz*Iy*p*q + Ixz*Iz*p*q + Ixz*mN + Iy*Iz*q*r - Iz**2*q*r + Iz*mL)/(Ix*Iz + Ixz**2)
qdot = (-Ix*p*r - Ixz*p**2 + Ixz*r**2 + Iz*p*r + mM)/Iy
rdot = (Ix**2*p*q - Ix*Ixz*q*r - Ix*Iy*p*q + Ix*mN - Ixz**2*p*q - Ixz*Iy*q*r + Ixz*Iz*q*r - Ixz*mL)/(Ix*Iz + Ixz**2)
p = p + dt * pdot
q = q + dt * qdot
r = r + dt * rdot
!update Euler rates
thetadot = q*cos(phi)-r*sin(phi)
phidot = p + q*sin(phi)*tan(theta) + r*cos(phi)*tan(theta)
psidot = (q*sin(phi) + r*cos(phi))/cos(theta)
!update distance
vinert=body2inert(vbody,[psi,phi,theta])
distance = distance + vinert*dt
!update Euler angles
theta = theta + thetadot*dt
phi = phi + phidot*dt
psi = psi + psidot*dt
write(1,1001) vbody(1), vbody(2), vbody(3), distance(1), distance(2), distance(3)
end do
write(*,*) vbody
write(*,*) distance
contains
function inert2body(vector, rot)
	!returns vector in body-centered co-ordinates, given rotation as theta, phi, psi
	implicit none
	double precision, dimension(3) :: inert2body
	double precision, dimension(3), intent(in) :: rot
	double precision, dimension(3), intent(in) :: vector
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
	implicit none
	double precision, dimension(3) :: body2inert
	double precision, dimension(3), intent(in) :: rot
	double precision, dimension(3), intent(in) :: vector
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
