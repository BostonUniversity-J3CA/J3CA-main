/*
 * BMP085Barometer.cpp
 *
 *  Created on: Apr 21, 2014
 *      Author: John R. Aleman, College of Engineering, Boston University
 *      Notes: This Definition of a class to interface with the
 *      Bosch BMP085 Digital pressure sensor was created based
 *      on the work of Derek Molloy.
 *      Copyright Derek Molloy, School of Electronic Engineering, Dublin City University
 *      www.eeng.dcu.ie/~molloyd/
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

#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stropts.h>
#include <stdio.h>
#include "BMP085Barometer.h"
#include <sys/time.h>
#include <iostream>
#include <math.h>
using namespace std;
#define MAX_BUS 64

//Sensor Data
#define DAT_MSB 	0x00 //0xF6
#define DAT_LSB 	0x01 //0xF7
#define DAT_XLSB 	0x02 //0xF8

//Calibration Data
#define AC1_M	 	0xAA
#define AC1_L	 	0xAB
#define AC2_M	 	0xAC
#define AC2_L	 	0xAD
#define AC3_M	 	0xAE
#define AC3_L	 	0xAF
#define AC4_M	 	0xB0
#define AC4_L	 	0xB1
#define AC5_M	 	0xB2
#define AC5_L	 	0xB3
#define AC6_M	 	0xB4
#define AC6_L	 	0xB5

#define B1_M	 	0xB6
#define B1_L	 	0xB7
#define B2_M	 	0xB8
#define B2_L	 	0xB9

#define MB_M	 	0xBA
#define MB_L	 	0xBB
#define MC_M	 	0xBC
#define MC_L	 	0xBD
#define MD_M	 	0xBE
#define MD_L	 	0xBF

//Configuration Parameters
#define SEL_BYTE   0xF4
#define TEMP_MODE  0x2E
#define PRESS_MODE 0xB4


BMP085Barometer::BMP085Barometer(int bus, int address) {
	I2CBus = bus;
	I2CAddress = address;
	readCalibrationData();
}

//********************************************************************************
// Necessary functions
//********************************************************************************

int BMP085Barometer::updateCheck(uint64_t time){
	if (time-this->lastUpdateTemp > 1000000 && this->waitingForUpdate == false){
		if(this->writeI2CDeviceByte(SEL_BYTE, TEMP_MODE)!=0){
			cout << "Failure to set selection byte value" << endl;
			return 1;
		}
		this->lastRequestTemp = time;
		this->waitingForUpdate = true;
		//cout << "flagggggggggg on" << endl;
		return 0;
	}
	if (time-this->lastUpdateTemp > 1000000 && this->waitingForUpdate == true && time-this->lastRequestTemp > 4500 && time-this->lastRequestTemp < 10000){
		if(this->readDataBuffers()!=0){
			cout << "Failure to read the buffers" << endl;
			return 1;
		}
		long ut = convertSigned16(DAT_MSB, DAT_LSB);
		long x1 = (ut-ac6)*ac5/(0x8000);
		//cout << x1 << endl;
		long x2 = (mc*0x800)/(x1+this->md);
		//cout << x2 << endl;
		this->b5 = 3672;//x1+x2;
		//cout << b5 << endl;
		this->Temperature = (this->b5+8)/0x10;
		//cout << this->Temperature << endl;


		this->lastUpdateTemp = time;
		this->waitingForUpdate = false;
		//cout << "flagggggggggg off" << endl;
		return 0;
	}

	if (this->waitingForUpdate == false){
		if(this->writeI2CDeviceByte(SEL_BYTE, PRESS_MODE)!=0){
			cout << "Failure to set selection byte value" << endl;
			return 1;
		}
		this->waitingForUpdate = true;
		//cout << "flag on" << endl;
		return 0;
	}
	if (time-lastUpdatePressure > 14000 && this->waitingForUpdate == true){
		if(this->readDataBuffers()!=0){
			cout << "Failure to read the buffers" << endl;
			return 1;
		}
		long up = convertPressure(DAT_MSB, DAT_LSB, DAT_XLSB);
		long b6 = this->b5-4000;
		long x1 = (this->b2*(b6*b6/0x1000))/0x800;
		long x2 = this->ac2*b6/0x800;
		long x3 = x1+x2;
		long b3 = ((this->ac1*4+x3)<<2)/4;
		x1 = this->ac3*b6/0x2000;
		x2 = (this->b1*(b6*b6/0x1000))/0x10000;
		x3 = ((x1+x2)+2)/4;
		unsigned long b4 = this->ac4*(unsigned long)(x3+32768)/0x8000;
		unsigned long b7 = ((unsigned long)up-b3)*(50000>>2);
		if(b7<0x80000000){
			this->Pressure = (b7*2/b4);
		}
		else{
			this->Pressure = (b7/b4)*2;
		}
		x1 = (this->Pressure/0x100)*(this->Pressure/0x100);
		x1 = (x1*3038)/0x10000;
		x2 = (-7357*this->Pressure)/0x10000;
		this->Pressure = this->Pressure+(x1+x2+3791)/16;
		this->lastUpdatePressure = time;
		this->waitingForUpdate = false;
		//cout << "flag off" << endl;
	}
	
	return 0;
}

int BMP085Barometer::readCalibrationData(){
    char namebuf[MAX_BUS];
   	snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", I2CBus);
    int file;
    if ((file = open(namebuf, O_RDWR)) < 0){
            cout << "Failed to open BMP085Barometer Sensor on " << namebuf << " I2C Bus" << endl;
            return(1);
    }
    if (ioctl(file, I2C_SLAVE, I2CAddress) < 0){
            cout << "I2C_SLAVE address " << I2CAddress << " failed..." << endl;
            return(2);
    }

    // In some i2c devices you need to send the first address
    // in write mode and then a stop/start condition is issued. Data bytes are
    // transferred with automatic address increment. 
    char buf[1] = { 0xAA };
    if(write(file, buf, 1) !=1){
    	cout << "Failed to Reset Address in readFullSensorState() " << endl;
    }

    int numberBytes = BMP085_CALIBRAION;
    int bytesRead = read(file, this->dataBuffer, numberBytes);
    if (bytesRead == -1){
    	cout << "Failure to read Byte Stream in readFullSensorState()" << endl;
    }
    close(file);

    if (this->dataBuffer[0x0f]!=0xd3){
    	cout << "MAJOR FAILURE: DATA WITH BMP085Barometer HAS LOST SYNC!" << endl;
    }
    cout << "Number of bytes read was " << bytesRead << "aadfad" << numberBytes << endl;
    for (int i=0; i<20; i++){
           printf("Byte %02d is 0x%02x\n", i, dataBuffer[i]);
    }
    cout << "Closing BMA180 I2C sensor state read" << endl;
    this->ac1 = convertSigned16(0x01, 0x00);
    cout << this->ac1 << endl;
	this->ac2 = convertSigned16(0x03, 0x02);
	this->ac3 = convertSigned16(0x05, 0x04);
	//cout << this->ac3 << endl;
	this->ac4 = convertUnSigned16(0x07, 0x06);
	//cout << this->ac4 << endl;
	this->ac5 = convertUnSigned16(0x09, 0x08);
	this->ac6 = convertUnSigned16(0x0b, 0x0a);
	this->b1  = convertSigned16(0x0d, 0x0c);
	this->b2  = convertSigned16(0x0f, 0x0e);
	this->mb  = convertSigned16(0x11, 0x010);
	this->mc  = convertSigned16(0x13, 0x12);
	cout << this->mc << endl;
	this->md  = convertSigned16(0x15, 0x14);
	cout << this->md << endl;

    return 0;
}

int BMP085Barometer::readDataBuffers(){
	
    char namebuf[MAX_BUS];
   	snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", I2CBus);
    int file;
    if ((file = open(namebuf, O_RDWR)) < 0){
            cout << "Failed to open L3G4200DGyroscope Sensor on " << namebuf << " I2C Bus" << endl;
            return(1);
    }
    if (ioctl(file, I2C_SLAVE, I2CAddress) < 0){
            cout << "I2C_SLAVE address " << I2CAddress << " failed..." << endl;
            return(2);
    }

    // In some i2c devices you need to send the first address
    // in write mode and then a stop/start condition is issued. Data bytes are
    // transferred with automatic address increment.
    char buf[1] = { 0xF6 };
    if(write(file, buf, 1) !=1){
    	cout << "Failed to Reset Address in readDataBuffers() " << endl;
    }

    int numberBytes = BMP085_I2C_BUFFER;
    int bytesRead = read(file, this->dataBuffer, numberBytes);
    if (bytesRead == -1){
    	cout << "Failure to read Byte Stream in readDataBuffers()" << endl;
    }
    close(file);

    //cout << "Number of bytes read was " << bytesRead << "aadfad" << numberBytes << endl;
    //for (int i=0; i<20; i++){
    //       printf("Byte %02d is 0x%02x\n", i, dataBuffer[i]);
    //}
    //cout << "Closing BMA180 I2C sensor state read" << endl;

    return 0;
}

int BMP085Barometer::convertSigned16(int msb_reg_addr, int lsb_reg_addr){
	short temp = dataBuffer[msb_reg_addr];
	temp = (temp<<8) | dataBuffer[lsb_reg_addr];
	//temp = ~temp + 1;
	return temp;
}

unsigned int BMP085Barometer::convertUnSigned16(int msb_reg_addr, int lsb_reg_addr){
	unsigned short temp = dataBuffer[msb_reg_addr];
	temp = (temp<<8) | dataBuffer[lsb_reg_addr];
	return temp;
}

int32_t BMP085Barometer::convertPressure(int msb_reg_addr, int lsb_reg_addr,int xlsb_reg_addr){
	int32_t temp = dataBuffer[msb_reg_addr];
	temp = ((temp<<16) | (dataBuffer[lsb_reg_addr]<<8) | (dataBuffer[lsb_reg_addr]))>>(6);
	return temp;
}

//********************************************************************************
// Extra functions
//********************************************************************************

int BMP085Barometer::writeI2CDeviceByte(char address, char value){

    //cout << "Starting BMP085 I2C sensor state write" << endl;
    char namebuf[MAX_BUS];
   	snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", I2CBus);
    int file;
    if ((file = open(namebuf, O_RDWR)) < 0){
            cout << "Failed to open ADX345 Sensor on " << namebuf << " I2C Bus" << endl;
            return(1);
    }
    if (ioctl(file, I2C_SLAVE, I2CAddress) < 0){
            cout << "I2C_SLAVE address " << I2CAddress << " failed..." << endl;
            return(2);
    }

    char buffer[2];
    	buffer[0] = address;
    	buffer[1] = value;
    if ( write(file, buffer, 2) != 2) {
        cout << "Failure to write values to I2C Device address." << endl;
        return(3);
    }
    close(file);
    //cout << "Finished BMP085Barometer I2C sensor state write" << endl;
    return 0;
}


BMP085Barometer::~BMP085Barometer() {
	// TODO Auto-generated destructor stub
}
