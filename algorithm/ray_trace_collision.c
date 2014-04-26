#ifndef RAY_TRACE_COLLISION_C
#define RAY_TRACE_COLLISION_C
#include <math.h>

int ray_trace_collision(double air_pos[],
			double air_prev[],
			double air_rad,			
			double obs_pos[],
			double obs_rad,
			double collision[]){
  /**
   * air_pos - aircraft's current position
   * air_prev - aircraft's last position (1 timestep before)
   * air_rad - aircraft's radius
   * obs_pos - obstacle's current position
   * obs_rad - the obstacle's radius
   * collision - a 3 element array that will be updated with the
   *      coordinates of a collision
   * This function returns TRUE if a collision is detected and FALSE
   * if no collision will occur. Works solely for a stationary obstacle
   */
  
  double dlon = air_pos[0] - air_prev[0];
  double dlat = air_pos[1] - air_prev[1];
  double dalt = air_pos[2] - air_prev[2];
  double radius = air_rad + obs_rad; // Add the radii of the 
  // aircraft and obstacle

  double a = dlon*dlon + dlat*dlat + dalt*dalt;
  double b = 
    2*dlon*(air_prev[0]-obs_pos[0]) + 
    2*dlat*(air_prev[1]-obs_pos[1]) + 
    2*dalt*(air_prev[2]-obs_pos[2]);

  double c = 
    pow(air_prev[0]-obs_pos[0],2.0) + 
    pow(air_prev[1]-obs_pos[1],2.0) + 
    pow(air_prev[2]-obs_pos[2],2.0) - (radius,2.0);

  double discriminant = pow(b,2.0) - 4*a*c;
  double t; // Time of collision
  if ( discriminant > 0 ){
    double t1 = (-b-sqrt(discriminant))/(2*a);
    double t2 = (-b+sqrt(discriminant))/(2*a);
    if ( t1 > 0 )
      t = t1;
    else if ( t2 > 0 )
      t = t2;
    collision[0] = air_prev[3] + t*dlon;
    collision[1] = air_prev[4] + t*dlat;
    collision[2] = air_prev[5] + t*dalt;
    return TRUE;
  }
  else 
    return FALSE;
};

#endif
