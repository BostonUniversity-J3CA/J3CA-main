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
!double precision function elevator
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
