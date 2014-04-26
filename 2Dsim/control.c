#include "constants.h"
#include "pathfunctions.c"
#include <stdio.h>
#define AVOIDHEIGHT 25.0
#define AVOIDDISTANCE 25.0
#define STARTDISTANCE (obstacleDistance-AVOIDDISTANCE)
#define PATHFUNCTION bump

double getelevator(double height, double heightcommand, double heightderivative, double pitch, double pitchrate)
{
//returns elevator deflection in degrees as a function of pitch in radians
double elevator = kheightchange*heightderivative+kheight*(height-heightcommand) + kpitch*(pitch-pitch0*3.141592653/180) + kdpitch*pitchrate;
return elevator;
}

double getthrottle(double velocity, double velocitySetpoint)
{
double throttle = kthrottle*(velocity-velocitySetpoint);
return throttle;
}

double getheight(double distance, double obstacleDistance)
{
if ( (distance<STARTDISTANCE) || (distance>(STARTDISTANCE+2*AVOIDDISTANCE)) )
	{return 0;}
else
	{
	if (distance<50)
		{return AVOIDHEIGHT*PATHFUNCTION((distance-STARTDISTANCE)/AVOIDDISTANCE);}
	else
		{return AVOIDHEIGHT*(PATHFUNCTION((2*AVOIDDISTANCE+STARTDISTANCE-distance)/AVOIDDISTANCE));}
	}
}

double getheightderivative(double distance, double obstacleDistance)
{
return getheight(distance+1, obstacleDistance)-getheight(distance, obstacleDistance);
}
