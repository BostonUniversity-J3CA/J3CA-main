/*
 * Control.c
 *
 *  Created on: Apr 30, 2014
 *      Author: John, L. Gillespie, John R. Aleman, Joseph E. Stone, Chirag Rathod, Ari J. Morse
 *      College of Engineering, Boston University
 *      Notes: Contains the PID loops
 *      Copyright G.R.A.M.S., College of Engineering, Boston University
 *      jaleman@bu.edu, chiragr314@gmail.com, johngillespie27@yahoo.com, jestone@bu.edu, amorse@bu.edu
 *
 * 		Redistribution and use in source and binary forms, with or without modification,
 * 		are permitted provided that the following conditions are met:
 * 			1. Redistributions of source code must retain the above copyright
 *    			notice, this list of conditions and the following disclaimer.
 * 			2. Redistributions in binary form must reproduce the above copyright
 *    			notice, this list of conditions and the following disclaimer in the
 *    			documentation and/or other materials provided with the distribution.
 *
 * 		THIS SOFTWARE IS PROVIDED ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * 		INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * 		AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL I
 * 		BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * 		CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * 		GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * 		HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * 		OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * 		SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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

