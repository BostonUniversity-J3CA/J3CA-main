#include "control.c"
#include "output.c"
#include "complementary.c"
#include "gps.cpp"
#include "imu.cpp"
#include "obstacle.cpp"
#include "../adsb_decode.h"
#include "./sensors/ADX345Accelerometer.cpp"
#include "./sensors/L3G4200DGyroscope.cpp"
#include <iostream>
using namespace std;

int initialize()
{
}

int main()
{
initialize(); //initializes accelerometer, etc.
float velocitySetpoint = 10; //intended speed of aircraft
float obstacleXYZ = {0,0,0} //location of obstacle
float x=0, y=0, z=0; //position
float vx=0, vy=0, vz=0; //velocities
int ax, ay, az; //accelerations
float pitch=0, roll=0, yaw=0; //orientation
float pitchrate=0, rollrate=0, yawrate=0; //orientation rates of change
float elevator=0, rudder=0, aileron=0, throttle=0; //actuator outputs
float height=0, heightcommand=0, heightderivative=0; //current height, current desired height, and desired rate of change in height
int i;
ADX345Accelerometer accelerometer(1, 0x53);
L3G4200DGyroscope gyroscope(1,0x69);
int accData[3] = {0,0,0};
int gyrData[3] = {0,0,0};
while (true)
	{
	//read accelerometer
	accelerometer.readFullSensorState();
	accData[0] = accelerometer.getAccelerationX();
	accData[1] = accelerometer.getAccelerationY();
	accData[2] = accelerometer.getAccelerationZ();
	//read gyroscope
	gyroscope.readFullSensorState();
	gyrData[0] = gyroscope.getAngularRateX();
	gyrData[1] = gyroscope.getAngularRateY();
	gyrData[2] = gyroscope.getAngularRateZ();
	//combine accelerometer and gyroscope
	complementaryFilter(accData, gyrData, &pitch, &roll);
	cout << "Pitch:" << pitch << "\tRoll:" << roll << "\n";
	//read asdb string, get obstacle position
	adsb_decode("AAABBBCCC", &obstacleXYZ);
	//get positions and velocities from gps (stub)
	gpsGET(x, y, z, vx, vy, vz);
	//get orientation and rates
	imuGET(pitch, roll, yaw, pitchrate, rollrate, yawrate);
	//get desired output (code from simulation)
	heightcommand = getheight(x, obstacleXYZ[0]);
	heightderivative = getheightderivative(x, obstacleXYZ[0]);
	elevator = getelevator(-z, heightcommand, heightderivative, pitch, pitchrate);
	rudder = getrudder(y, yaw); //need constants (set to zero for now)
	aileron = getaileron(roll); //need constants (set to zero for now)
	throttle = getthrottle(vx, velocitySetpoint);
	//stubs to set outputs
	setElevator(elevator);
	setRudder(rudder);
	setAileron(aileron);
	setThrottle(throttle);
//	cout << "Elevator: " << elevator << "\tRudder: " << rudder << "\tAileron: " << aileron <<"\tThrottle:"<<throttle<<"\n";
//	cout << "Acc X: " << accData[0] << "\tAcc Y: " << accData[1] << "\tAcc Z: " << accData[2] << "\n";
	}
}
