#include "control.c"
#include "output.c"
#include "gps.cpp"
#include "imu.cpp"
#include "obstacle.cpp"
#include <iostream>
using namespace std;

int initialize()
{
}

int main()
{
initialize(); //initializes accelerometer, etc.
double velocitySetpoint = 10; //intended speed of aircraft
double obstacleX = 50; //location of obstacle
double x=0, y=0, z=0; //position
double vx=0, vy=0, vz=0; //velocities
double pitch=0, roll=0, yaw=0; //orientation
double pitchrate=0, rollrate=0, yawrate=0; //orientation rates of change
double elevator=0, rudder=0, aileron=0, throttle=0; //actuator outputs
double height=0, heightcommand=0, heightderivative=0; //current height, current desired height, and desired rate of change in height
int i;
for (i=0; i<10000; i++)
	{
	//get positions and velocities from gps (stub)
	gpsGET(x, y, z, vx, vy, vz);
	//get orientation and rates
	imuGET(pitch, roll, yaw, pitchrate, rollrate, yawrate);
	//get obstacle location
	obstacleX = obstacleGET();
	//get desired output (code from simulation)
	heightcommand = getheight(x, obstacleX);
	heightderivative = getheightderivative(x, obstacleX);
	elevator = getelevator(-z, heightcommand, heightderivative, pitch, pitchrate);
	rudder = getrudder(y, yaw); //need constants (set to zero for now)
	aileron = getaileron(roll); //need constants (set to zero for now)
	throttle = getthrottle(vx, velocitySetpoint);
	//stubs to set outputs
	setElevator(elevator);
	setRudder(rudder);
	setAileron(aileron);
	setThrottle(throttle);
	cout << elevator << rudder << aileron << throttle;
	}
}
