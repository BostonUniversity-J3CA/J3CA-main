#include "constants.h"
#include "pathfunctions.c"
#include <stdio.h>
#define AVOIDHEIGHT 25.0
#define AVOIDDISTANCE 25.0
#define STARTDISTANCE (obstacleDistance-AVOIDDISTANCE)
#define PATHFUNCTION bump

float getelevator(float height, float heightcommand, float heightderivative, float pitch, float pitchrate)
{
//returns elevator deflection in degrees as a function of pitch in radians
float elevator = kheightchange*heightderivative+kheight*(height-heightcommand) + kpitch*(pitch-pitch0*3.141592653/180) + kdpitch*pitchrate;
return elevator;
}

float getrudder(float y, float yaw)
{
return ky*y + kyaw*yaw;
}

float getaileron(float roll)
{
return kroll*roll;
}

float getthrottle(float velocity, float velocitySetpoint)
{
float throttle = kthrottle*(velocity-velocitySetpoint);
return throttle;
}

float getheight(float distance, float obstacleDistance)
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

float getheightderivative(float distance, float obstacleDistance)
{
return getheight(distance+1, obstacleDistance)-getheight(distance, obstacleDistance);
}

