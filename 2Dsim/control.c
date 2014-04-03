#include "constants.h"
#include "pathfunctions.c"
#include <stdio.h>
#define AVOIDHEIGHT 15.0
#define AVOIDDISTANCE 25.0
#define STARTDISTANCE 25.0
#define PATHFUNCTION bump

double getelevator(double height, double heightcommand, double heightderivative, double pitch, double pitchrate)
{
//returns elevator deflection in degrees as a function of pitch in radians
double elevator = kheightchange*heightderivative+kheight*(height-heightcommand) + kpitch*(pitch-pitch0*3.141592653/180) + kdpitch*pitchrate;
return elevator;
}

double getthrottle(double velocity)
{
double throttle = kthrottle*(velocity-10);
return throttle;
}

double getheight(double distance)
{
if (distance<25 || distance >75)
	{return 0;}
else
	{
	if (distance<50)
		{return AVOIDHEIGHT*PATHFUNCTION((distance-STARTDISTANCE)/AVOIDDISTANCE);}
	else
		{return AVOIDHEIGHT*(PATHFUNCTION((2*AVOIDDISTANCE+STARTDISTANCE-distance)/AVOIDDISTANCE));}
	}
}

double getheightderivative(double distance)
{
return getheight(distance+1)-getheight(distance);
}
