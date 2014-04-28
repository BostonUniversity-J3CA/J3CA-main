#include "constants.h"
#include "pathfunctions.c"
#include <stdio.h>
#define AVOIDHEIGHT 25.0
#define AVOIDDISTANCE 25.0
#define STARTDISTANCE (obstacleDistance-AVOIDDISTANCE)
#define PATHFUNCTION level

float getelevator(float height, float heightcommand, float heightderivative, float pitch, float pitchrate)
{
//returns elevator deflection in degrees as a function of pitch in radians
static float heightint = 0;
float heighterror = (height-heightcommand);
heightint += heighterror;
static float pitchint = 0;
float pitcherror = (pitch-pitch0);
pitchint += pitcherror;
float elevator = kheightchange*heightderivative
	+kheight*heighterror +iheight*heightint
	+kpitch*pitcherror +ipitch*pitchint +kdpitch*pitchrate;
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

