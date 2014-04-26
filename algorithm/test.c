#include <stdio.h>
#include <math.h>
#include "algorithm.c"

int comment;

int main(int argc, char argv[]){
  double air_pos[] = {55.0,409.8,0.0};
  double air_prev[]= {50.0,409.8,0.0};
  double air_vel[] = {2.732,0.0,0.0};
  double air_rad   = 0.5;
  double obs_pos[] = {80.0,408.5,0.0};
  double obs_vel[] = {-3.870,0.0,0.0};
  double obs_rad   = 13.66;

  double collision_point[3];

  int ray;
  int *rp;

  rp = &ray;
  
  int collide = detect_collision_point(air_pos,
			 air_prev,
			 air_vel,
			 air_rad,
			 obs_pos,
			 obs_vel,
			 obs_rad,
			 collision_point,
			 rp
			 );
  printf("Will collide: %i\n%i,%f\n",collide,ray,collision_point[0]);
  return 0;
};
