/**
 * This file implements:
 * simple_path,
 * This file cannot run with the math.h header file
 */

// This function creates the simple "bump" trajectory in 2D
// cur_pos is our aircraft's position (only longitude and altitude are used)
// target_pos is point we want our aircraft to pass through
// finalYPos is the altitude of our original trajectory
// xpos is an array of our aircraft's and the obstacle's longitude position
//     IMPORTANT: xpos[0] = our aircraft longitude, xpos[1] = obstacle longitude-position
int simple_path(const int cur_pos[], const int target_pos[], const int finalYPos, const int xpos[], const int obstacle_radius){
  if ( cur_pos[0] < target_pos[0] ){
    if ( cur_pos[1] < target_pos[1] ){
      return exp( -target_pos[1] / ( target_pos[1]*BUMP_COEFF ) );
    }
    else {
      return 0;
    }
  }
  else {
    if ( cur_pos[1] > target_pos[1] ){
      if ( xpos[0] - ( xpos[1] + obstacle_radius ) > DESC_DIST ){
	return -exp( -target_pos[1] / ( target_pos[1]*BUMP_COEFF ) );
      }
    } 
    return 0;
  }
  return 0;
}
