//============================================================================
// Name        : AccTest.cpp
// Author      : John R Aleman
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include "ADX345Accelerometer.h"
#include "L3G4200DGyroscope.h"
#include "HMC5883LMagnetometer.h"
#include "BMP085Barometer.h"
#include "BMP085Barometer.cpp"
#include "ServoAttach.h"
//#include "./BMP085Barometer.cpp"
#include <sys/time.h>
//#include <ctime>
#include <stdint.h>
#include <string>
#include <fstream>
#define THROTLE_ADDRESS "/sys/devices/ocp.3/pwm_test_P8_13.11"
//#define AILERON_ADDRESS "/sys/devices/ocp.3/pwm_test_P8_19.12"
#define ELEVATOR_ADDRESS "/sys/devices/ocp.3/pwm_test_P9_14.12"
//#define RUDDER_ADDRESS "/sys/devices/ocp.3/pwm_test_P8_16.14 "
//#define RIGHT_FLAP__ADDRESS "/sys/devices/ocp.3/pwm_test_P8_22.16"
//#define LEFT_FLAP_ADDRESS "/sys/devices/ocp.3/pwm_test_P8_21.15"

using namespace std;

int main() {

	uint64_t orig_time;
	struct timeval time_count;
	gettimeofday(&time_count,NULL);
	orig_time = time_count.tv_sec*(uint64_t)1000000+time_count.tv_usec;

	cout << "Servo set test " << endl;



	//char addr[64];
    //snprintf(addr, sizeof(addr), "%s" ,THROTLE_ADDRESS);
	//ServoAttach Throttle (addr);
	//Throttle.setPeriod(500002);


	BMP085Barometer Barometer(1,0x77);
	

    /*
	//Accelerometer Initialization
	ADX345Accelerometer Accelerometer(1,0x53); //0x53 is the Accelerometer address
	if (Accelerometer.getTIME_FF()!=0x14){
		Accelerometer.setTIME_FF(0x14); //100ms free fall interrupt
	}
    if (Accelerometer.getDATA_FORMAT()!=0x0a){
    	Accelerometer.setDATA_FORMAT(0x0a);  //Full resolution +- 8g
    }
    if (Accelerometer.getPOWER_CTL()!=0x08){
    	Accelerometer.setPOWER_CTL(0x08); //Always measure and never sleep
    }
    if (Accelerometer.getBW_RATE()!=0x0a){
    	Accelerometer.setBW_RATE(0x0a);  //0x0a fo 100Hz, 0x0c for 400hz
    }

    //Gyroscope Initialization
    L3G4200DGyroscope Gyroscope(1,0x69); //0x69 is the Gyroscope address

    if (Gyroscope.getCTRL_REG1()!=0x0f){
    	Gyroscope.setCTRL_REG1(0x0f); //Enables three axis and sets 100hz
    }
    if (Gyroscope.getCTRL_REG2()!=0x20){
    	Gyroscope.setCTRL_REG2(0x20); //Normal mode no high Pass
    }
    if (Gyroscope.getCTRL_REG3()!=0x00){
       	Gyroscope.setCTRL_REG3(0x00); //FIFO and interrupt configuration
    }
    if (Gyroscope.getCTRL_REG4()!=0x00){
       	Gyroscope.setCTRL_REG4(0x00); //Data format and bus selection
    }
    if (Gyroscope.getCTRL_REG5()!=0x00){
       	Gyroscope.setCTRL_REG5(0x00); //FIFO and interrupt enable
    }
    */

    /*
    //Magnetometer Initialization
    HMC5883LMagnetometer Magnetometer(1,0x1e); //0x1e is the Magnetometer address

    if (Magnetometer.getCONF_REG_A()!=0x18){
    	Magnetometer.setCONF_REG_A(0x18); //Data Rate and data averaging
    }

    if (Magnetometer.getCONF_REG_B()!=0x20){
        	Magnetometer.setCONF_REG_B(0x20); //Gain
        }

    if (Magnetometer.getMODE_REG()!=0x00){
        	Magnetometer.setMODE_REG(0x00); //Continious Mode
        }
	*/

    cout << "And we are out" << endl;


    while(1){
    	gettimeofday(&time_count,NULL);
    	orig_time = time_count.tv_sec*(uint64_t)1000000+time_count.tv_usec;
        Barometer.updateCheck(orig_time);
        //Magnetometer.readFullSensorState();
        int x = Barometer.getTemperature();
        int y = Barometer.getPressure();
        int z = 0;
        //int z = Magnetometer.getGaussZ();
        cout << x << "," << y << "," << z << endl;
     }

    /* Gyro test
    while(1){
    		Gyroscope.readFullSensorState();
    		int x = Gyroscope.getAngularRateX();
    		int y = Gyroscope.getAngularRateY();
    		int z = Gyroscope.getAngularRateZ();
    		cout << x << "," << y << "," << z << endl;
    }
    */


    /* ACC test
    while(1){
		Accelerometer.readFullSensorState();
		int x = Accelerometer.getAccelerationX();
		int y = Accelerometer.getAccelerationY();
		int z = Accelerometer.getAccelerationZ();
		cout << x << "," << y << "," << z << endl;
	}
	*/


    /*   GPIO Test
	cout << "Program begins here" << endl;
	FILE *LEDHandle = NULL;
	const char *LEDBrightness = "/sys/class/leds/beaglebone:green:usr3/brightness";

	for (int i=0;i<10;i++){
		if((LEDHandle = fopen(LEDBrightness, "r+"))!=NULL){
			fwrite("1", sizeof(char), 1, LEDHandle);
			fclose(LEDHandle);
		}
		sleep(1);

		if((LEDHandle = fopen(LEDBrightness, "r+"))!=NULL){
			fwrite("0", sizeof(char), 1, LEDHandle);
			fclose(LEDHandle);
		}
		sleep(1);
	}

	cout << "Out of program" << endl;
    */

	return 0;
}
