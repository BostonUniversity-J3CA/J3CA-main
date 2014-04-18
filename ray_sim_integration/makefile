run : sim.o aero.o control.o normal.o algorithm.o
	gcc -o run sim.o aero.o control.o normal.o algorithm.o -lgfortran

normal.o : normal.f90
	gcc -c normal.f90

sim.o : sim.f90
	gcc -c sim.f90

aero.o : aero.f90
	gcc -c aero.f90

control.o : control.c constants.h pathfunctions.c
	gcc -c control.c

algorithm.o : ../algorithm/test.c ../algorithm/algorithm.c ../algorithm/ray_trace_collision.c ../algorithm/detect_collision_point.c ../algorithm/simple_path.c
	gcc -c ../algorithm/algorithm.c -lm

clean :
	rm sim.o aero.o control.o normal.o
