#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stropts.h>
#include <stdio.h>
#include "ADX345Accelerometer.h"
#include <iostream>
#include <math.h>
using namespace std;
#define MAX_BUS 64

//Sensor Data
#define ACC_X_LSB 	0x32
#define ACC_X_MSB 	0x33
#define ACC_Y_LSB 	0x34
#define ACC_Y_MSB 	0x35
#define ACC_Z_LSB 	0x36
#define ACC_Z_MSB 	0x37

//Configuration Parameters
#define TIME_FF     0x29
#define DATA_FORMAT 0x31  //0x0A
#define POWER_CTL   0x2D
#define BW_RATE 	 0x2C

#define TEMP	  	0x08  //Temperature must be removed for ACC


ADX345Accelerometer::ADX345Accelerometer(int bus, int address) {
	I2CBus = bus;
	I2CAddress = address;
	readFullSensorState();
}

//********************************************************************************
// Necessary functions
//********************************************************************************

int ADX345Accelerometer::readFullSensorState(){

   //cout << "Starting ADX345 I2C sensor state read" << endl;
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

    // In some i2c devices you need to send the first address
    // in write mode and then a stop/start condition is issued. Data bytes are
    // transferred with automatic address increment.
    char buf[1] = { 0x00 };
    if(write(file, buf, 1) !=1){
    	cout << "Failed to Reset Address in readFullSensorState() " << endl;
    }

    int numberBytes = ADX345_I2C_BUFFER;
    int bytesRead = read(file, this->dataBuffer, numberBytes);
    if (bytesRead == -1){
    	cout << "Failure to read Byte Stream in readFullSensorState()" << endl;
    }
    close(file);

    if (this->dataBuffer[0]!=0xe5){
    	cout << "MAJOR FAILURE: DATA WITH ADX345 HAS LOST SYNC!" << endl;
    }

    this->accelerationX = convertAcceleration(ACC_X_MSB, ACC_X_LSB);
    this->accelerationY = convertAcceleration(ACC_Y_MSB, ACC_Y_LSB);
    this->accelerationZ = convertAcceleration(ACC_Z_MSB, ACC_Z_LSB);
    //cout << "Pitch:" << this->getPitch() << "   Roll:" << this->getRoll() <<  endl;
    return 0;
}

int ADX345Accelerometer::convertAcceleration(int msb_reg_addr, int lsb_reg_addr){
//	cout << "Converting " << (int) dataBuffer[msb_reg_addr] << " and " << (int) dataBuffer[lsb_reg_addr] << endl;;
	short temp = dataBuffer[msb_reg_addr];
	temp = (temp<<8) | dataBuffer[lsb_reg_addr];
	//temp = temp>>2;
	temp = ~temp + 1;
//	cout << "The X acceleration is " << temp << endl;
	return temp;
}

//********************************************************************************
// Extra functions
//********************************************************************************


void ADX345Accelerometer::displayMode(int iterations){

	for(int i=0; i<iterations; i++){
		this->readFullSensorState();
		printf("Rotation (%d, %d, %d)", accelerationX, accelerationY, accelerationZ);
	}
}

uint8_t ADX345Accelerometer::getTIME_FF(){
	this->readFullSensorState();
	char temp = dataBuffer[TIME_FF];
	this->data_format = (uint8_t) temp;
	return this->data_format;
}

int ADX345Accelerometer::setTIME_FF(uint8_t desired){
	if(this->writeI2CDeviceByte(TIME_FF, desired)!=0){
		cout << "Failure to update TIME_FF value" << endl;
		return 1;
	}
	return 0;
}

uint8_t ADX345Accelerometer::getDATA_FORMAT(){
	this->readFullSensorState();
	char temp = dataBuffer[DATA_FORMAT];
	this->data_format = (uint8_t) temp;
	return this->data_format;
}

int ADX345Accelerometer::setDATA_FORMAT(uint8_t desired){
	if(this->writeI2CDeviceByte(DATA_FORMAT, desired)!=0){
		cout << "Failure to update DATA_FORMAT value" << endl;
		return 1;
	}
	return 0;
}

uint8_t ADX345Accelerometer::getPOWER_CTL(){
	this->readFullSensorState();
	char temp = dataBuffer[POWER_CTL];
	this->data_format = (uint8_t) temp;
	return this->data_format;
}

int ADX345Accelerometer::setPOWER_CTL(uint8_t desired){
	if(this->writeI2CDeviceByte(POWER_CTL, desired)!=0){
		cout << "Failure to update POWER_CTL value" << endl;
		return 1;
	}
	return 0;
}

uint8_t ADX345Accelerometer::getBW_RATE(){
	this->readFullSensorState();
	char temp = dataBuffer[BW_RATE];
	this->data_format = (uint8_t) temp;
	return this->data_format;
}

int ADX345Accelerometer::setBW_RATE(uint8_t desired){
	if(this->writeI2CDeviceByte(BW_RATE, desired)!=0){
		cout << "Failure to update BW_RATE value" << endl;
		return 1;
	}
	return 0;
}

int ADX345Accelerometer::writeI2CDeviceByte(char address, char value){

    cout << "Starting ADX345 I2C sensor state write" << endl;
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
    cout << "Finished ADX345 I2C sensor state write" << endl;
    return 0;
}

ADX345Accelerometer::~ADX345Accelerometer() {
	// TODO Auto-generated destructor stub
}
