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

float getthrottle(float velocity)
{
float throttle = 10 - velocity;
printf("%f\n", velocity);
return throttle;
}

int test(int input)
{
return input+2;
}

