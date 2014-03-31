run : sim.o aero.o control.o normal.o
	gcc -o run sim.o aero.o control.o normal.o -lgfortran

normal.o : normal.f90
	gcc -c normal.f90

sim.o : sim.f90
	gcc -c sim.f90

aero.o : aero.f90
	gcc -c aero.f90

control.o : control.c constants.h pathfunctions.c
	gcc -c control.c

clean :
	rm sim.o aero.o control.o normal.o
