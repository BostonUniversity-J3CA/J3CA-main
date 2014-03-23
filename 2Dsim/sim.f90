program simulate
implicit none
!gravity (m/s**2) 
double precision, parameter :: g=9.80665D0
double precision, parameter :: pi=3.14159265358979323846264338D0
!pi
!timing variables (s)
double precision :: time=0D0, endtime=35D0, dt=.001D0
!rate for control loop (s)
double precision :: update = .001D0
!mass (kg)
double precision :: m = 2D0
!angle of attack, coefficient of lift
double precision :: alpha = 0D0, Cl
!control variables
double precision :: throttle, elevator
!Forces (thrust, lift, and drag)
double precision :: T, L, D
!pitch moment
double precision :: moment
!aircraft velocity, body frame
double precision :: vxbody = 10D0, vybody = 0D0
!aircraft velocity, inertial frame: horizontal/vertical
double precision :: vx = 10D0, vy = 0D0
!aircraft pitch
double precision :: pitch=1D-1
!pitch angular velocity and acceleration
double precision :: omega=0, omegadot=0
!moment of inertia (kg*m**2)
double precision :: I = .06
!distance: horizontal/vertical
double precision :: x=0, y= 0
!wind
!double precision, dimension(3) :: wind = [0D0, 0D0, 0D0]
!random number
double precision :: rand
interface
	real(c_double) function getThrottle(velocity) bind(c)
		!returns throttle from external c function
		use iso_c_binding
		implicit none
		real (c_double), VALUE :: velocity
	end function
	real(c_double) function getElevator(altitude, pitch, pitchrate) bind(c)
		!returns throttle from external c function
		use iso_c_binding
		implicit none
		real (c_double), VALUE :: altitude, pitch, pitchrate
	end function
	double precision function thrust(throttle)
		!returns thrust (in N) as a function of throttle (in RPM)
		implicit none
		double precision, intent(in) :: throttle
	end function
	real function nrand()
	end function
	subroutine init_random_seed()
	end subroutine
	double precision function pitchElevator(elevator)
		double precision, intent(in) :: elevator
	end function
	double precision function pitchDamp(pitchrate)
		double precision, intent(in) :: pitchrate
	end function
	double precision function lift(Cl, vAir)
		double precision, intent(in) :: Cl, vAir
	end function
	double precision function drag(Cl, vAir)
		double precision, intent(in) :: Cl, vAir
	end function
	double precision function liftCoeff(alpha)
		double precision, intent(in) :: alpha
	end function
end interface
open(unit = 1, file = "sim.dat")
1001 format(f6.2,T10,f6.2,T20,f6.2,T30,f6.2,T40,f6.2,T50,f6.2, T60, f6.2, T70, f6.2, T80, f6.2, T90, f6.2, T100, f6.2)
call init_random_seed()
write(1,*) "vx vy vxbody vybody x y omega pitch alpha"
do while (time<endtime)
!write(*,*) elevator, moment, pitch, alpha, omega
time = time + dt
!if (nint(time/update) == floor(time/update)) then
!get control inputs
throttle = getThrottle(vx)
elevator = getElevator(y+nrand(), pitch, omega)
!end if
!calculate body velocities
vxbody = vx*cos(pitch)+vy*sin(pitch)
vybody = vy*cos(pitch)-vx*sin(pitch)
!calculate angle of attack
alpha = atan(-vy/vx)+pitch
!calculate forces
Cl = liftCoeff(alpha)
L = lift(Cl, vxbody)
D = drag(Cl, vxbody)
T = thrust(throttle)
moment = pitchElevator(elevator)
!calculate acceleration, update velocities
vx = vx + ((T-D)*cos(pitch)-L*sin(pitch))*dt/m
vy = vy + ((T-D)*sin(pitch)+L*cos(pitch)-g)*dt/m
!solve for pitch acceleration, pitch rate, and pitch
omegadot = moment/I
omega = omega + dt * omegadot
pitch = pitch + dt * omega
!update distance
x = x + vx * dt
y = y + vy * dt
write(1,1001) vx, vy, vxbody, vybody, x, y, omega*180/pi, pitch*180/pi, alpha*180/pi
end do
write(*,*) vxbody, vybody
write(*,*) x, y
end program
