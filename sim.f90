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
!control variables
double precision :: throttle, aileron, Cl
do while (time<endtime)
throttle = getThrottle()
aileron = getAileron()
time = time + dt
L = lift(Cl, vAir)
D = drag(Cl, vAir)
vAir = vAir + ((throttle-D)/m-g*sin(gammaAir)) * dt
gammaAir = gammaAir + ( (L*cos(phi)-m*g*cos(gammaAir)) / (m*vAir) ) * dt
p = p + (rollDamp(p) + rollAileron(aileron)) * dt
psidot = ( L*sin(phi) / (m*vAir*cos(gammaAir)) ) 
phi = phi + (p + psidot * sin(theta))
end do
contains
pure function getAileron()
	!returns aileron deflection
	double precision :: getAileron=0
end function
pure function getThrottle()
	!returns throttle
	double precision :: getThrottle=1
end function
pure function rollAileron(aileron)
	!returns roll moment as a function of aileron deflection 
	implicit none
	double precision, intent(in) :: aileron 
	double precision :: rollDamp
	!constant of proportionality
	double precision :: kAileron = 1
	rollAileron = kAileron*aileron
end function
pure function rollDamp(p)
	!returns damping moment as a function of roll rate
	implicit none
	double precision, intent(in) :: p
	double precision :: rollDamp
	!damping constant
	double precision :: damping = 1
	rollDamp = - damping * p
end function
pure function lift(Cl, vAir)
	!returns lift as a function of Cl and velocity 
	implicit none
	double precision, intent(in) :: elevator, vAir
	double precision :: rho = 1.275 !kg/m**3
	lift = .5 * rho * vAir*vAir * Cl
end function
pure function drag(Cl, vAir)
	!returns drag as a function of Cl and velocity 
	implicit none
	double precision, intent(in) :: elevator, vAir
	double precision :: rho = 1.275 !kg/m**3
	double precision :: Cd0=.02, k=.001
	drag = .5 * rho * vAir*vAir * (Cd0 + k * Cl**Cl)
end function
end program simulate
