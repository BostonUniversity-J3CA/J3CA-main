#ifndef SIMPLE_PATH_H
#define SIMPLE_PATH_H

// Defines the steepness of the bump curve
const int BUMP_COEFF;
// Defines the amount of distance that our aircraft must have between itself
// and the obstacle before descending to the original trajectory's altitude
const int DESC_DIST;

int simple_path(const int cur_pos[], const int target_pos[], const int finalY, const int xpos[], const int obstacle_radius);
#endif
