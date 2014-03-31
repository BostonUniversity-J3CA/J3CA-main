#include <math.h>
#include <stdio.h>

//Possible trajectories
//Each is normalized for domain 0<x<1 and range 0<y<1
//Called by control.c

double step(double x)
{ return 1; }

double linear(double x)
{ return x; }

double sigmoid(double x)
{ return 1.31303528546*(1/(exp(-(4*x-2))+1)-.11920292202);}

double arcs(double x)
{
//Not Done !!!!
if ( x<.5 )
	{ return .5-sqrt(.5*.5-x*x); }
else
	{ return 1; }
}

double bump(double x)
{
x--;
if ( fabs(x)<1 )
	{return exp(-1/(1-x*x)); }
else
	{return 0; }
}
