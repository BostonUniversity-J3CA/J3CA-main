#include <stdio.h>
#include "constants.h"

//control functions for use in simulation and in controlling aircraft
double getaileron()
{
return 0;
}

double getelevator(float pitch, float pitchrate)
{
float elevator = kpitch*(pitch-pitch0*3.141592653/180) + kdpitch*pitchrate;
return elevator;
}

double getrudder(float yaw)
{
return kyaw*yaw;
}

float getthrottle(float velocity)
{
float throttle = kthrottle*(velocity-10);
return throttle;
}

int test(int input)
{
return input+2;
}

