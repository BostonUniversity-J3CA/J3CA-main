/**
 * This file implements the detect_collision_point function.
 * The math.h header, ray_tracing.h header, AND calculate_t.h header are both 
 * required for this function to run properly. 
 */

bool detect_collision_point(const int aircraft[], const int obstacle[], const int aircraft_vel[], const int obtacle_vel[], int collision_point[], bool *ray){
  bool valid_t;
  int  collision_2d[3];
  t = calculate_t(aircraft,obstacle,aircraft_vel,obstacle_vel,&valid_t);
  if ( valid_t == false ){
    if ( ray_tracing(aircraft,obstacle,aircraft[3]+obstacle[3],collision_2d) ){
      *ray = true;
      return true;
    }
    else {
      return false;
    }
  }
  else {
    collision_point[0] = aircraft[0] + aircraft_vel[0]*t;
    collision_point[1] = aircraft[1] + aircraft_vel[1]*t;
    collision_point[2] = aircraft[2] + aircraft_vel[2]*t;
    *ray = false;
    return true;
  }
}
