#ifndef SIMPLE_PATH_C
#define SIMPLE_PATH_C
#include <math.h>
double simple_path(const double our_pos[], const double obsx, 
		   const double obs_radius, const double target_alt,
		   const double orig_alt, const double bump_coeff, 
		   const double avoid_by){
  /**
   * double ourx_pos- our aircraft's current position [long,lat,alt]
   * double obsx- the obstacle's position in the x-direction (longitude?)
   * doulbe obs_radius- the obstacle's radius
   * double target_alt- the altitude the aircraft wants to reach
   * double orig_alt- the aircraft's original altitude before replanning
   * double avoid_by- the number of meters to avoid the obstacle by
   * double bump_coeff- the coefficient that decides the steepness of 
   *      our incline. The max is 
   */
  if ( fabs(our_pos[0] - obsx) < (avoid_by + obs_radius) ){
    if ( our_pos[2] < target_alt )
      return exp(-target_alt/(target_alt*bump_coeff));
    else
      return 0.0;
  }
  else {
    if ( our_pos[2] > orig_alt )
      return -exp(-orig_alt/(orig_alt*bump_coeff));
    else
      return 0.0;
  }
  return 0.0;
}
#endif
