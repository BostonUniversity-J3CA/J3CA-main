#include <stdio.h>
#include <math.h>

int FALSE = 0;
int TRUE  = 1;

int ray_trace_collision(double aircraft[],
			double obstacle[],
			double collision[]);

int main(){
  double aircraft[] = {5,0,20,
		       4,0,20,
		       6};
  double obstacle[] = {100,0,20,5};
  double collision[3];

  int willCollide = ray_trace_collision(aircraft,obstacle,collision);
  printf("%f,%f,%f\n",collision[0],collision[1],collision[2]);
  return 0;
};
int ray_trace_collision(double aircraft[], 
			double obstacle[], 
			double collision[]){
  /**
   * aircraft - a 7 element array containing: current GPS coordinates,
   *      it's previous GPS coordinates ( 1 time step before ), and 
   *      the aircraft's radius
   * obstacle - a 4 element array containing: current GPS coordinates
   *      and the obstacle's radius
   * collision - a 3 element array that will be updated with the
   *      coordinates of a collision
   * This function returns TRUE if a collision is detected and FALSE
   * if no collision will occur. Works solely for a stationary obstacle
   */
  
  double dlon = aircraft[0] - aircraft[3];
  double dlat = aircraft[1] - aircraft[4];
  double dalt = aircraft[2] - aircraft[5];
  double radius = aircraft[6] + obstacle[3]; // Add the radii of the 
  // aircraft and obstacle

  double a = dlon*dlon + dlat*dlat + dalt*dalt;
  double b = 
    2*dlon*(aircraft[3]-obstacle[0]) + 
    2*dlat*(aircraft[4]-obstacle[1]) + 
    2*dalt*(aircraft[5]-obstacle[2]);

  double c = 
    pow(aircraft[3]-obstacle[0],2.0) + 
    pow(aircraft[4]-obstacle[1],2.0) + 
    pow(aircraft[5]-obstacle[2],2.0) - (radius,2.0);

  double discriminant = pow(b,2.0) - 4*a*c;
  double t; // Time of collision
  if ( discriminant > 0 ){
    double t1 = (-b-sqrt(discriminant))/(2*a);
    double t2 = (-b+sqrt(discriminant))/(2*a);
    if ( t1 > 0 )
      t = t1;
    else if ( t2 > 0 )
      t = t2;
    collision[0] = aircraft[3] + t*dlon;
    collision[1] = aircraft[4] + t*dlat;
    collision[2] = aircraft[5] + t*dalt;
    return TRUE;
  }
  else 
    return FALSE;
};
