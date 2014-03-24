#include "constants.h"
#include <stdio.h>

//control functions for use in simulation and in controlling aircraft
float getaileron()
{
return 0;
}

double getelevator(double height, double pitch, double pitchrate)
{
double elevator = kheight*height + kpitch*(pitch-pitch0*3.141592653/180) + kdpitch*pitchrate;
return elevator;
}

float getrudder(float yaw)
{
return kyaw*yaw;
}

double getthrottle(double velocity)
{
double throttle = kthrottle*(velocity-10);
return throttle;
}

