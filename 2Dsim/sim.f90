program simulate
implicit none
!gravity (m/s**2) 
double precision, parameter :: g=9.80665D0
double precision, parameter :: pi=3.14159265358979323846264338D0
!pi
!timing variables (s)
double precision :: time=0D0, endtime=100D0, dt=.0001D0
!Update rate for control loop and for GPS (Hz)
integer :: update = 100, gpsupdate = 20
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
double precision :: vxbody, vybody
!aircraft velocity, inertial frame: horizontal/vertical
double precision :: vx = 10D0, vy = 0D0
!aircraft pitch
double precision :: pitch=1D-1
!pitch angular velocity and acceleration
double precision :: omega=0, omegadot=0
!moment of inertia (kg*m**2)
double precision :: I = .06
!distance: horizontal/vertical, gps readings
double precision :: x=0, y=0, gpsx=0, gpsy=0
!random number
double precision :: rand
!counting value
integer :: counting=0
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
	double precision function thrust(throttle, velocity)
		!returns thrust (in N) as a function of throttle (in RPM)
		implicit none
		double precision, intent(in) :: throttle, velocity
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
time = time + dt
if (mod(counting*gpsupdate, nint(1/dt)) == 0) then
gpsy = y+nrand()
end if
if (mod(counting*update, nint(1/dt)) == 0) then
!get control inputs
throttle = getThrottle(vx)
elevator = getElevator(gpsy,  pitch, omega)
end if
!calculate body velocities
vxbody = vx*cos(pitch)+vy*sin(pitch)
vybody = vy*cos(pitch)-vx*sin(pitch)
!calculate angle of attack
alpha = atan(-vy/vx)+pitch
!calculate forces
Cl = liftCoeff(alpha)
L = lift(Cl, vxbody)
D = drag(Cl, vxbody)
T = thrust(throttle, vxbody)
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
if (mod(counting*100, nint(1/dt)) == 0) then
write(1,1001) vx, vy, vxbody, vybody, x, y, omega*180/pi, pitch*180/pi, alpha*180/pi
end if
counting = counting + 1
end do
write(*,*) vxbody, vybody
write(*,*) x, y
end program
