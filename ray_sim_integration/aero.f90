double precision function pitchElevator(elevator, velocity)
	implicit none
	!returns pitch moment as a function of elevator deflection in degrees
	double precision, intent(in) :: elevator, velocity
	pitchElevator = .020872845 * (velocity**2) * (elevator*3.14159265359/180)
end function
double precision function pitchDamp(q)
	!returns damping moment as a function of pitch rate
	implicit none
	double precision, intent(in) :: q
	!damping constant
	double precision :: damping = 0
	pitchDamp = - damping * q
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
	drag = .5 * rho * vAir*vAir * (Cd0 + k * Cl*Cl)
end function
double precision function liftCoeff(alpha)
	!returns lift coefficient as a function of angle of attack
	implicit none
	double precision, intent(in) :: alpha
	double precision :: Cl0=0
	double precision :: Clalpha=6
	liftCoeff = Cl0 + Clalpha*alpha
end function
double precision function thrust(throttlecommand, velocity)
	!returns thrust (in N) as a function of throttle (in RPM)
	implicit none
	!inputs of propeller speed (RPM) and aircraft velocity (m/s)
	double precision, intent(in) :: throttlecommand, velocity
	!diameter of propeller in inches
	double precision :: throttle
	double precision, parameter :: diameter = 8
	!advance ratio = velocity/n, thrust coefficient = thrust/n**2
	double precision :: J, kT
	if (throttlecommand .LE. 0) then
		thrust = 0
	else
		throttle = min(throttlecommand, 11000.0)
		J = 2362.20472 * velocity/(throttle*diameter)
		if (J .LE. 1.28458906314633D-1) then
			kT = -3.25686575113504D-8*J + 1.17507574470878D-8
		else
			kT = -1.26852416676591D-8*J + 9.19655559400817D-9
		end if
		thrust = 4.44822162 * kT*throttle**2 !converted to N from lbf
	end if
end function
