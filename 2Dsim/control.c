#include "constants.h"
#include <stdio.h>

//control functions for use in simulation and in controlling aircraft

double getelevator(double height, double pitch, double pitchrate)
{
//returns elevator deflection in degrees as a function of pitch in radians
double elevator = kheight*height + kpitch*(pitch-pitch0*3.141592653/180) + kdpitch*pitchrate;
return elevator;
}

double getthrottle(double velocity)
{
double throttle = kthrottle*(velocity-10);
return throttle;
}

