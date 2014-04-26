#include "constants.h"
#include "pathfunctions.c"
#include <stdio.h>
#define AVOIDHEIGHT 15.0
#define AVOIDDISTANCE 15.0
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

double getheight(double distance, double distance2collision)
{
if (distance < STARTDISTANCE || distance > STARTDISTANCE+AVOIDDISTANCE*2)
	{return 0;}
else
	{
	if (distance<(STARTDISTANCE+AVOIDDISTANCE))
		{return AVOIDHEIGHT*PATHFUNCTION((distance-STARTDISTANCE)/AVOIDDISTANCE);}
	else
		{return AVOIDHEIGHT*(PATHFUNCTION((2*AVOIDDISTANCE+STARTDISTANCE-distance)/AVOIDDISTANCE));}
	}
}

double collisiondistance(double x, double  y, double  obsX, double  obsY, double  xvelocity, double  yvelocity)
{
double air_pos[] = {0.0,0.0,0.0};
double air_rad = 5.0;
double obs_pos[] = {50.0,0.0,0.0};
double obs_rad = 1000.0;
double collision[] = {0.0,0.0,0.0};
air_pos[0] = x;
air_pos[1] = y;
double air_prev[] = {0.0,0.0,0.0};
air_prev[0]=air_pos[0]-xvelocity;
air_prev[1]=air_pos[1]-yvelocity;
int willCollide = ray_trace_collision(air_pos, air_prev, air_rad, obs_pos, obs_rad, collision);
return collision[0]+air_pos[0];
}
  
double getheightderivative(double distance, double distance2collision)
{
return getheight(distance+1, distance2collision)-getheight(distance, distance2collision);
}
