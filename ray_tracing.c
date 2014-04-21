/**
 * This file implements the ray tracing collision detection function that is
 * used to detect collisions with obstacles that are stationary and moving
 * along the same trajectory line as our aircraft.
 */

// aircraft[] and obstacle[] will contain the same elements:
// current position, previous position, and radius. so:
// aircraft[6] = {x,y,z,xprev,yprev,zprev,radius};
bool ray_tracing(const int aircraft[], const int obstacle[], int collision_point[]){
  int t  = -1;
  int dx = aircraft[0] - aircraft[3];
  int dy = aircraft[1] - aircraft[4];
  int dz = aircraft[2] - aircraft[5];

  int a = dx*dx + dy*dy + dz*dz;
  int b = 2*dx*(aircraft[3]-obstacle[0])+2*dy*(aircraft[4]-obstacle[1])+2*dz*(aircraft[5]-obstacle[2]);
  int c = (aircraft[3]-obstacle[0])^2+(aircraft[4]-obstacle[1])^2+(aircraft[5]-obstacle[2])^2-(aircraft[6]+obstacle[6])^2;

  int discriminant = b^2 - 4*a*c;
  if ( discriminant >= 0 ){
    int t1 = (-b-sqrt(b^2-4*a*c))/(2*a);
    int t2 = (-b+sqrt(b^2-4*a*c))/(2*a);
    if ( t1 > 0 ){
      t = t1;
    }
    else if ( t2 > 0 ){
      t = t2;
    }
    collision_point[0] = aircraft[3] + t*dx;
    collision_point[1] = aircraft[4] + t*dy;
    collision_point[2] = aircraft[5] + t*dz;
    return true;
  }
  else {
    return false;
  }
}
