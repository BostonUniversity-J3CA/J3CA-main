#include <stdio.h>
//control functions for use in simulation and in controlling aircraft
double getaileron()
{
return 0;
}

double getelevator()
{
return 0;
}

double getrudder()
{
return 0;
}

double getthrottle(double velocity)
{
double throttle = 10 - velocity;
printf("%f\n", throttle);
return throttle;
}

