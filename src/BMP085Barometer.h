/*
 * BMP085Barometer.h
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

#ifndef BMP085BAROMETER_H_
#define BMP085BAROMETER_H_
#define BMP085_I2C_BUFFER 0x03
#define BMP085_CALIBRAION 0x16

class BMP085Barometer {

private:
	int I2CBus, I2CAddress;
	char dataBuffer[BMP085_I2C_BUFFER];
        uint64_t lastUpdatePressure;
	uint64_t lastUpdateTemp;
	uint64_t lastRequestTemp;
	bool waitingForPresUpdate;
        bool waitingForTempUpdate;

	int16_t ac1;
	int16_t ac2;
	int16_t ac3;
	uint16_t ac4;
	uint16_t ac5;
	uint16_t ac6;
	int16_t b1;
	int16_t b2;
	int16_t mb;
	int16_t mc;
	int16_t md;

	long b5;

	long Temperature;
	long Pressure;

	int  convertSigned16(int msb_addr, int lsb_addr);
	unsigned int  convertUnSigned16(int msb_addr, int lsb_addr);
	int32_t  convertPressure(int msb_reg_addr, int lsb_reg_addr,int xlsb_reg_addr);
	int  writeI2CDeviceByte(char address, char value);

public:
	BMP085Barometer(int bus, int address);

	int updateCheck(uint64_t time);
	int readCalibrationData();
	int readDataBuffers();
	// The following do physical reads and writes of the sensors

	long getTemperature() { return Temperature; }
	long getPressure() { return Pressure; }

	virtual ~BMP085Barometer();
};

#endif /* BMP085BAROMETER_H_ */











