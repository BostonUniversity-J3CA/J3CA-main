real function nrand()
	implicit none
	!returns a normally distributed random number with
	!standard deviation of 1
	real :: u, v, s
	u = 2*rand()-1
	v = 2*rand()-1
	s = u**2 + v**2
	do while (s >= 1 .or. s == 0)
		u = 2*rand()-1
		v = 2*rand()-1
		s = u**2 + v**2
	end do
	nrand = sqrt(-2*log(s)) * (u/sqrt(s))
end function

subroutine init_random_seed()
integer :: seed, un
open(unit=un, file="/dev/urandom", access="stream")
read(un) seed
call srand(seed)
end subroutine
