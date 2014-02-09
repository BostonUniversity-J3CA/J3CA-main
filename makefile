simulate : sim.o aero.o control.o
	gcc -o simulate sim.o aero.o control.o -lgfortran

sim.o : sim.f90
	gcc -c sim.f90

aero.o : aero.f90
	gcc -c aero.f90

control.o : control.c
	gcc -c control.c
