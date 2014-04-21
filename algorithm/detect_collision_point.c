#ifndef DETECT_COLLISION_POINT_C
#define DETECT_COLLISION_POINT_C

#include "calculate_t.c"

int detect_collision_point(double air_pos[],
			   double air_prev[],
			   double air_vel[],
			   double air_rad,
			   double obs_pos[],
			   double obs_vel[],
			   double obs_rad,
			   double collision_point[],
			   int *ray){
  /**
   * air_pos - aircraft's current position (3 elements)
   * air_prev- aircraft's previous position (3 elements)
   * air_vel - aircraft's current velocity (3 elements)
   * air_rad - aircraft's radius
   * obs_pos - obstacle's current position (3 elements)
   * obs_vel - obstacle's current velocity (3 elements)
   * collision_point - point where collision will occur. This function
         updates this array ( NOTE: must contain space for 3 double
         values )
   * *ray - TRUE (1) if static ray detection was used otherwise FALSE (0)
   */

  double t = calculate_t(air_pos,
			 air_vel,
			 air_rad,
			 obs_pos,
			 obs_vel,
			 obs_rad,
			 ray
			); 
  if ( *ray == TRUE ){
    return ray_trace_collision(air_pos,
			       air_prev,
			       air_rad,
			       obs_pos,
			       obs_rad,
			       collision_point);
  }
  else {
    collision_point[0] = air_pos[0] + air_vel[0]*t;
    collision_point[1] = air_pos[1] + air_vel[1]*t;
    collision_point[2] = air_pos[2] + air_vel[2]*t;
    *ray = FALSE;
    return TRUE;
  }
}

#endif
