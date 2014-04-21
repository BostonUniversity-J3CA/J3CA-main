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
using namespace std;

int main() {


	cout << "Reading Acc data test 11" << endl;


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


    sleep(5);

    while(1){
    		Gyroscope.readFullSensorState();
    		int x = Gyroscope.getAngularRateX();
    		int y = Gyroscope.getAngularRateY();
    		int z = Gyroscope.getAngularRateZ();
    		cout << x << "," << y << "," << z << endl;
    }


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
