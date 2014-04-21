#include <math.h>
#include <stdio.h>

//Possible trajectories
//Each is normalized for domain 0<x<1 and range 0<y<1
//Called by control.c

float level(float x)
{ return 0; }
float step(float x)
{ return 1; }

float linear(float x)
{ return x; }

float sigmoid(float x)
{ return 1.31303528546*(1/(exp(-(4*x-2))+1)-.11920292202);}

float arcs(float x)
{
//Not Done !!!!
if ( x<.5 )
	{ return .5-sqrt(.5*.5-x*x); }
else
	{ return 1; }
}

float bump(float x)
{
x--;
if ( fabs(x)<1 )
	{return exp(-1/(1-x*x)); }
else
	{return 0; }
}
