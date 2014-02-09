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
double precision function pitchElevator(elevator)
	implicit none
	!returns pitch moment as a function of elevator deflection 
	double precision, intent(in) :: elevator 
	!constant of proportionality
	double precision :: kElevator = 1
	pitchElevator = kElevator*elevator
end function
double precision function pitchDamp(q)
	!returns damping moment as a function of pitch rate
	implicit none
	double precision, intent(in) :: q
	!damping constant
	double precision :: damping = 1
	pitchDamp = - damping * q
end function
double precision function yawRudder(rudder)
	implicit none
	!returns yaw moment as a function of rudder deflection 
	double precision, intent(in) :: rudder 
	!constant of proportionality
	double precision :: kRudder = 1
	yawRudder = kRudder*rudder
end function
double precision function yawDamp(r)
	!returns damping moment as a function of yaw rate
	implicit none
	double precision, intent(in) :: r
	!damping constant
	double precision :: damping = 1
	yawDamp = - damping * r
end function
double precision function lift(Cl, vAir)
	!returns lift as a function of Cl and velocity 
	implicit none
	double precision, intent(in) :: Cl, vAir
	double precision :: rho = 1.275 !kg/m**3
	lift = .5 * rho * vAir*vAir * Cl
end function
double precision function drag(Cl, vAir)
	!returns drag as a function of lift coefficient  and velocity 
	implicit none
	double precision, intent(in) :: Cl, vAir
	double precision :: rho = 1.275 !kg/m**3
	double precision :: Cd0=.02, k=.001
	drag = .5 * rho * vAir*vAir * (Cd0 + k * Cl**Cl)
end function
double precision function liftCoeff(alpha)
	!returns lift coefficient as a function of angle of attack
	implicit none
	double precision, intent(in) :: alpha
	double precision :: Cl0=.3
	double precision :: Clalpha=6
	liftCoeff = Cl0 + Clalpha*alpha
end function
