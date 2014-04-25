/*
 * HMC5883LMagnetometer.cpp
 *
 *  Created on: Apr 21, 2014
 *      Author: John R. Aleman, College of Engineering, Boston University
 *      Notes: This Definition of a class to interface with the
 *      Honeywell HMC5883L Digital Compass was created based
 *      on the work of Derek Molloy.
 *      Copyright Derek Molloy, School of Electronic Engineering, Dublin City University
 *      www.eeng.dcu.ie/~molloyd/
 *
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
#include "HMC5883LMagnetometer.h"
#include <iostream>
#include <math.h>
using namespace std;
#define MAX_BUS 64

//Sensor Data
#define MAG_X_LSB 	0x04
#define MAG_X_MSB 	0x03
#define MAG_Y_LSB 	0x08
#define MAG_Y_MSB 	0x07
#define MAG_Z_LSB 	0x06
#define MAG_Z_MSB 	0x05

//Configuration Parameters

#define CONF_REG_A  0x00
#define CONF_REG_B  0x01
#define MODE_REG    0x02

HMC5883LMagnetometer::HMC5883LMagnetometer(int bus, int address) {
	I2CBus = bus;
	I2CAddress = address;
	readFullSensorState();
}


//********************************************************************************
// Necessary functions
//********************************************************************************

int HMC5883LMagnetometer::readFullSensorState(){

   //cout << "Starting HMC5883L I2C sensor state read" << endl;
    char namebuf[MAX_BUS];
   	snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", I2CBus);
    int file;
    if ((file = open(namebuf, O_RDWR)) < 0){
            cout << "Failed to open HMC5883L Sensor on " << namebuf << " I2C Bus" << endl;
            return(1);
    }
    if (ioctl(file, I2C_SLAVE, I2CAddress) < 0){
            cout << "I2C_SLAVE address " << I2CAddress << " failed..." << endl;
            return(2);
    }

    // In some i2c devices you need to send the first address
    // in write mode and then a stop/start condition is issued. Data bytes are
    // transferred with automatic address increment.
    char statusreg[1] = {0x09};
    if(write(file, statusreg, 1) !=1){
        cout << "Failed to Reset Address in readFullSensorState() " << endl;
    }
    char status[1];
    int bytesRead;
    int numberBytes = HMC5883L_I2C_BUFFER;
    if (read(file,status,1)<3){
    	char buf[1] = { 0x03 };
        if(write(file, buf, 1) !=1){
        	cout << "Failed to Reset Address in readFullSensorState() " << endl;
        }
        bytesRead = read(file, this->dataBuffer, numberBytes);
        if (bytesRead == -1){
        	cout << "Failure to read Byte Stream in readFullSensorState()" << endl;
        }
    }
    //printf("Status is  %02x \n", status[0]);
    close(file);

    //if (this->dataBuffer[0x0a]!=0x48){
    //	cout << "MAJOR FAILURE: DATA WITH HMC5883L HAS LOST SYNC!" << endl;
    //}
    //cout << "Number of bytes read was " << bytesRead << endl;
    //for (int i=0; i<numberBytes; i++){
    //       printf("Byte %02x is 0x%02x\n", i, dataBuffer[i]);
    //}
    //cout << "Closing I2C sensor state read" << endl;

    this->gaussX = convert(MAG_X_MSB, MAG_X_LSB);
    this->gaussY = convert(MAG_Y_MSB, MAG_Y_LSB);
    this->gaussZ = convert(MAG_Z_MSB, MAG_Z_LSB);
    return 0;
}

int HMC5883LMagnetometer::convert(int msb_reg_addr, int lsb_reg_addr){
	short temp = dataBuffer[msb_reg_addr];
	temp = (temp<<8) | dataBuffer[lsb_reg_addr];
	//temp = temp>>2;
	temp = ~temp + 1;
	return temp;
}

//********************************************************************************
// Extra functions
//********************************************************************************


void HMC5883LMagnetometer::displayMode(int iterations){

	for(int i=0; i<iterations; i++){
		this->readFullSensorState();
		printf("Rotation (%d, %d, %d)", gaussX, gaussY, gaussZ);
	}
}
//
uint8_t conf_reg_A;
	uint8_t conf_reg_B;
	uint8_t mode_reg;

//


uint8_t HMC5883LMagnetometer::getCONF_REG_A(){
	char namebuf[MAX_BUS];
   	snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", I2CBus);
    int file;
    if ((file = open(namebuf, O_RDWR)) < 0){
            cout << "Failed to open HMC5883L Sensor on " << namebuf << " I2C Bus" << endl;
            return(1);
    }
    if (ioctl(file, I2C_SLAVE, I2CAddress) < 0){
            cout << "I2C_SLAVE address " << I2CAddress << " failed..." << endl;
            return(2);
    }
    // In some i2c devices you need to send the first address
    // in write mode and then a stop/start condition is issued. Data bytes are
    // transferred with automatic address increment.
    char reg[1] = {CONF_REG_A};
    if(write(file, reg, 1) !=1){
       cout << "Failed to Reset Address in getXXX() " << endl;
    }
    char payload[1];
    read(file, payload, 1);
    close(file);
	char temp = payload[0];
	this->conf_reg_A = (uint8_t) temp;
	return this->conf_reg_A;
}

int HMC5883LMagnetometer::setCONF_REG_A(uint8_t desired){
	if(this->writeI2CDeviceByte(CONF_REG_A, desired)!=0){
		cout << "Failure to update CONF_REG_A value" << endl;
		return 1;
	}
	return 0;
}

uint8_t HMC5883LMagnetometer::getCONF_REG_B(){
	char namebuf[MAX_BUS];
   	snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", I2CBus);
    int file;
    if ((file = open(namebuf, O_RDWR)) < 0){
            cout << "Failed to open HMC5883L Sensor on " << namebuf << " I2C Bus" << endl;
            return(1);
    }
    if (ioctl(file, I2C_SLAVE, I2CAddress) < 0){
            cout << "I2C_SLAVE address " << I2CAddress << " failed..." << endl;
            return(2);
    }
    // In some i2c devices you need to send the first address
    // in write mode and then a stop/start condition is issued. Data bytes are
    // transferred with automatic address increment.
    char reg[1] = {CONF_REG_B};
    if(write(file, reg, 1) !=1){
       cout << "Failed to Reset Address in getXXX() " << endl;
    }
    char payload[1];
    read(file, payload, 1);
    close(file);
	char temp = payload[0];
	this->conf_reg_B = (uint8_t) temp;
	return this->conf_reg_B;
}

int HMC5883LMagnetometer::setCONF_REG_B(uint8_t desired){
	if(this->writeI2CDeviceByte(CONF_REG_B, desired)!=0){
		cout << "Failure to update CONF_REG_B value" << endl;
		return 1;
	}
	return 0;
}

uint8_t HMC5883LMagnetometer::getMODE_REG(){
	char namebuf[MAX_BUS];
   	snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", I2CBus);
    int file;
    if ((file = open(namebuf, O_RDWR)) < 0){
            cout << "Failed to open HMC5883L Sensor on " << namebuf << " I2C Bus" << endl;
            return(1);
    }
    if (ioctl(file, I2C_SLAVE, I2CAddress) < 0){
            cout << "I2C_SLAVE address " << I2CAddress << " failed..." << endl;
            return(2);
    }
    // In some i2c devices you need to send the first address
    // in write mode and then a stop/start condition is issued. Data bytes are
    // transferred with automatic address increment.
    char reg[1] = {MODE_REG};
    if(write(file, reg, 1) !=1){
       cout << "Failed to Reset Address in getXXX() " << endl;
    }
    char payload[1];
    read(file, payload, 1);
    close(file);
	char temp = payload[0];
	this->mode_reg = (uint8_t) temp;
	return this->mode_reg;
}

int HMC5883LMagnetometer::setMODE_REG(uint8_t desired){
	if(this->writeI2CDeviceByte(MODE_REG, desired)!=0){
		cout << "Failure to update MODE_REG value" << endl;
		return 1;
	}
	return 0;
}

int HMC5883LMagnetometer::writeI2CDeviceByte(char address, char value){

    cout << "Starting HMC5883L I2C sensor state write" << endl;
    char namebuf[MAX_BUS];
   	snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", I2CBus);
    int file;
    if ((file = open(namebuf, O_RDWR)) < 0){
            cout << "Failed to open HMC5883LMagnetometer Sensor on " << namebuf << " I2C Bus" << endl;
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
    cout << "Finished HMC5883LMagnetometer I2C sensor state write" << endl;
    return 0;
}

HMC5883LMagnetometer::~HMC5883LMagnetometer() {
	// TODO Auto-generated destructor stub
}

