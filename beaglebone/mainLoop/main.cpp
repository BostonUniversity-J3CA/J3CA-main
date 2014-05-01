/*
 * Main Code
 *
 *
 *  Created on: Apr 30, 2014
 *      Author: John, L, Gillespie, John R. Aleman, Joseph E. Stone, Chirag Rathod, Ari J. Morse
 *      College of Engineering, Boston University
 *      Notes: Main code for Pitch stabilization of a fixed wing aircraft and sensor data aquisition as well as
 *      ground control station communication using the Beaglebone Black.
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



#include "control.c"
#include "output.c"
#include "complementary.c"
#include "gps.cpp"
#include "./sensors/ADX345Accelerometer.cpp"
#include "./sensors/L3G4200DGyroscope.cpp"
#include "./sensors/HMC5883LMagnetometer.cpp"
#include "./sensors/BMP085Barometer.h"
#include "./sensors/BMP085Barometer.cpp"
#include "./sensors/ServoAttach.h"
#include "./sensors/ServoAttach.cpp"
#include "../adsb_decode.h"
#include "write_data.h"
#include "readGPS.h"
#include "serial_write.h"
#include <sys/time.h>
#include <iostream>
#include <string>
#include <stdint.h>
#include <fstream>
#define THROTLE_ADDRESS "/sys/devices/ocp.3/pwm_test_P8_13.11"
#define ELEVATOR_ADDRESS "/sys/devices/ocp.3/pwm_test_P9_14.12"
using namespace std;


const int 	MANUAL		= 1;
const int 	AUTONOMOUS= 0;
const double 	CHECK_GPS = (1/10)*1000000; // Check the GPS buffer every 10 times per second

int initialize(ADX345Accelerometer &accelerometer, L3G4200DGyroscope &gyroscope, HMC5883LMagnetometer &Magnetometer){
	if (accelerometer.getTIME_FF()!=0x14){
		accelerometer.setTIME_FF(0x14); //100ms free fall interrupt
	}
	if (accelerometer.getDATA_FORMAT()!=0x0a){
		accelerometer.setDATA_FORMAT(0x0a);	//Full resolution +- 8g
	}
	if (accelerometer.getPOWER_CTL()!=0x08){
		accelerometer.setPOWER_CTL(0x08); //Always measure and never sleep
	}
	if (accelerometer.getBW_RATE()!=0x0a){
		accelerometer.setBW_RATE(0x0a);	//0x0a fo 100Hz, 0x0c for 400hz
	}
	if (gyroscope.getCTRL_REG1()!=0x0f){
		gyroscope.setCTRL_REG1(0x0f); //Enables three axis and sets 100hz
	}
	if (gyroscope.getCTRL_REG2()!=0x20){
		gyroscope.setCTRL_REG2(0x20); //Normal mode no high Pass
	}
	if (gyroscope.getCTRL_REG3()!=0x00){
			 	gyroscope.setCTRL_REG3(0x00); //FIFO and interrupt configuration
	}
	if (gyroscope.getCTRL_REG4()!=0x00){
		gyroscope.setCTRL_REG4(0x00); //Data format and bus selection
	}
	if (gyroscope.getCTRL_REG5()!=0x00){
		gyroscope.setCTRL_REG5(0x00); //FIFO and interrupt enable
	}
	// Initialize magnetometer
	if (Magnetometer.getCONF_REG_A()!=0x18){
		Magnetometer.setCONF_REG_A(0x18); //Data Rate and data averaging
	}
	
	if (Magnetometer.getCONF_REG_B()!=0x20){
		Magnetometer.setCONF_REG_B(0x20); //Gain
	}
		
	if (Magnetometer.getMODE_REG()!=0x00){
		Magnetometer.setMODE_REG(0x00); //Continious Mode
	}
}
int main(){
	make_file_name(); // Finds the next file to save the data to
	file.open(fname,fstream::app);
	
	long pressure0 = 0;
        long pressure;
        long temperature;
	int flight_type	 = MANUAL;
	int flight_number = 0;
	int num_obstacles	= 0;
	char xbee_port[]	= {"/dev/ttyO4"};
	char data_buf[20] = {'\0'};
	// Clear data.dat
	ofstream fp;
	fp.open("data.dat",fstream::out | fstream::trunc);
	fp.close();

	struct termios newtio;
	int fd = openGPS(&newtio);
	int xbee = open_port(xbee_port);
	struct timeval tinit, tlast, tcurrent, tgpsread;
	float velocitySetpoint = 10; //intended speed of aircraft
	float obstacleXYZ[3]={30000,30000,30000}; //location of obstacle
	float x=0, y=0, z=0, zgps; //position
	float vx=0, vy=0, vz=0; //velocities
	float pitch=0, roll=0, yaw=0; //orientation
	float pitchrate=0, rollrate=0, yawrate=0; //orientation rates of change
	float elevator=0, rudder=0, aileron=0, throttle=0; //actuator outputs
	float height=0, heightcommand=0, heightderivative=0; //current height, current desired height, and desired rate of change in height
	int i;
	ADX345Accelerometer accelerometer(1,0x53);
	L3G4200DGyroscope gyroscope(1,0x69);
	HMC5883LMagnetometer Magnetometer(1,0x1e); //0x1e is the Magnetometer address
	BMP085Barometer Barometer(1,0x77);
        char addr[64];
        snprintf(addr,sizeof(addr), "%s", THROTLE_ADDRESS);
        ServoAttach Throttle (addr);
        Throttle.setPeriod(20000000);
        Throttle.setDuty(1000000);
        Throttle.setPolarity(0);
        snprintf(addr,sizeof(addr),"%s",ELEVATOR_ADDRESS);
        ServoAttach Elevator(addr);
        Elevator.setPeriod(20000000);
        Elevator.setDuty(1500000);
        Elevator.setPolarity(0);
	initialize(accelerometer, gyroscope, Magnetometer); //initializes accelerometer, etc.
	int accData[3] = {0,0,0};
	int gyrData[3] = {0,0,0};
	int compData[3]= {0,0,0};
	float time;
	int num_satellites, fixQuality=0;
	string nmeaSentence;
	float x0=0, y0=0, z0=0;
	float distance=0;

	//zero GPS
	gettimeofday(&tinit,NULL);
	printf("Searching for fix\n");
	//discard first 500 readings from barometer
	int success;
	for (i=0; i<200; i++) {
		gettimeofday(&tlast,NULL);
		success = Barometer.updateCheck((uint64_t)(tlast.tv_sec*1000000+tlast.tv_usec));
		tlast = tcurrent;
		gettimeofday(&tcurrent,NULL);
	}
	tgpsread = tlast;
	//average next 10 for "sea level pressure"
	sleep(5);
	long pressure0sum = 0;
	for (i=0; i<10000; i++) {
		success = Barometer.updateCheck((uint64_t)(tlast.tv_sec*1000000+tlast.tv_usec));
		pressure0 =  Barometer.getPressure();
		pressure0sum += pressure0;
		tlast = tcurrent;
		gettimeofday(&tcurrent,NULL);
		//printf("Pressure is %ld\n", pressure0);
	}
	pressure0sum=0;
	for (i=0; i<20; i++) {
		success = Barometer.updateCheck((uint64_t)(tlast.tv_sec*1000000+tlast.tv_usec));
		pressure0 =  Barometer.getPressure();
		pressure0sum += pressure0;
		tlast = tcurrent;
		gettimeofday(&tcurrent,NULL);
	}
	tcurrent = tlast;
	pressure0 = pressure0sum/20;
	while (fixQuality<1){
	readGPS(fd,&x,&y,&z,&num_satellites,&fixQuality);
	switch (fixQuality){
			case 0:
				printf(".");
				break;
			case 1:
				printf("Fix but no WAS\n");
				break;
			case 2:
				printf("Fix with WAS\n");
				break;
			default:
				break;
		}
	}
	x0=x;
	y0=y;
	z0=z;
	while (true){
		//read barometer
		Barometer.updateCheck((uint64_t)(tlast.tv_sec*1000000+tlast.tv_usec));
		pressure = Barometer.getPressure();
                temperature = Barometer.getTemperature();
		z = 44330*(1-pow(((float)pressure/(float)pressure0),(1./5.255)));
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
		// read magnetometer
		Magnetometer.readFullSensorState();
		compData[0] = Magnetometer.getGaussX();
		//sleep(1);
		compData[1] = Magnetometer.getGaussY();
		compData[2] = Magnetometer.getGaussZ();
		//combine accelerometer and gyroscope, update pitch roll yaw
		complementaryFilter(accData, gyrData, &pitch, &roll, &yaw);
		//update pitch roll and yaw rates
		pitchrate = gyrData[1];
		rollrate = gyrData[0];
		yawrate = gyrData[2];
		//get desired output (code from simulation)
		heightcommand = getheight(distance, obstacleXYZ[0]);
		heightderivative = getheightderivative(distance, obstacleXYZ[0]);
		elevator = getelevator(-z, heightcommand, heightderivative, pitch, pitchrate);
		rudder = getrudder(y, yaw); //need constants (set to zero for now)
		aileron = getaileron(roll); //need constants (set to zero for now)
		throttle = getthrottle(vx, velocitySetpoint);
		//stubs to set outputs
		Elevator.setDuty(setElevator(elevator));
		setRudder(rudder);
		setAileron(aileron);
		setThrottle(throttle);
		//	cout << "Pitch:" << pitch << "\tRoll:" << roll << "\n";
		//	cout << "Elevator: " << elevator << "\tRudder: " << rudder << "\tAileron: " << aileron <<"\tThrottle:"<<throttle<<"\n";
		//	cout << "Acc X: " << accData[0] << "\tAcc Y: " << accData[1] << "\tAcc Z: " << accData[2] << "\n";
		// SEND DATA
		/*char f[4];
		char a[1];
		a[0] = 0xfa;
		write(xbee,a,1);								 // 0xfa
		cout << a << " ";
		memcpy(a,&flight_type,1);				// Manual (1) or Auto (0)
		write(xbee,a,1);
		cout << a << " ";
		memcpy(a,&flight_number,1);			// Flight number
		write(xbee,a,1);
		cout << a << " ";
		memcpy(a,&fixQuality,1);				 // GPS Fix Quality
		write(xbee,f,4);
		memcpy(f,&x,4);									// Longitude
		cout << f << " ";
		write(xbee,f,4);
		memcpy(f,&y,4);									// Latitude
		write(xbee,f,4);
		cout << f << " ";
		memcpy(f,&z,4);									// Altitude
		write(xbee,f,1);
		cout << f << " ";
		memcpy(a,&num_satellites,1);		 // # of Satellites
		write(xbee,a,1);
		cout << f << " ";
		memcpy(a,&num_obstacles,1);			// # of Obstacles
		write(xbee,a,1);
		cout << a << endl;*/
		tlast=tcurrent;
		gettimeofday(&tcurrent,NULL);
//		printf("%f m from start\n", distance);
		write_data((tcurrent.tv_sec-tinit.tv_sec)*1000000+(tcurrent.tv_usec-tinit.tv_usec),
				 (tcurrent.tv_sec-tlast.tv_sec)*1000000+(tcurrent.tv_usec-tlast.tv_usec),
				 "m", (x-x0),(y-y0),z,
				 roll,pitch,yaw,
				 accData,compData,gyrData,
				 temperature,pressure,fixQuality,num_satellites,0);
		if (	((tcurrent.tv_sec-tgpsread.tv_sec)*1000000+(tcurrent.tv_usec-tgpsread.tv_usec)) >= CHECK_GPS ){
			// Reset the initial time
			tgpsread=tcurrent;
			readGPS(fd,&x,&y,&zgps,&num_satellites,&fixQuality);
			distance = (x-x0)*(x-x0)+(y-y0)*(y-y0)+(z)*(z) ;
		}
	}
}
