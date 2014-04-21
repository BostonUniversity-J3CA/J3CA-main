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
using namespace std;

int main() {


	cout << "Reading Acc data test 11" << endl;
	ADX345Accelerometer Accelerometer(1,0x53);
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

    sleep(5);

	while(1){
		Accelerometer.readFullSensorState();
		int x = Accelerometer.getAccelerationX();
		int y = Accelerometer.getAccelerationY();
		int z = Accelerometer.getAccelerationZ();
		cout << x << "," << y << "," << z << endl;
	}


    /*
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
