#include <stdio.h>
#include "constants.h"

//control functions for use in simulation and in controlling aircraft
double getaileron()
{
return 0;
}

double getelevator(float pitch, float altitude)
{
float elevator = kpitch*pitch + kaltitude*altitude;
return elevator;
}

double getrudder()
{
return 0;
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

