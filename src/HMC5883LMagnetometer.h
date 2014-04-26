/*
 * HMC5883LMagnetometer.h
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


#ifndef HMC5883LMAGNETOMETER_H_
#define HMC5883LMAGNETOMETER_H_
#define HMC5883L_I2C_BUFFER 0x06

class HMC5883LMagnetometer {
private:
	int I2CBus, I2CAddress;
	char dataBuffer[HMC5883L_I2C_BUFFER];

	int gaussX;
	int gaussY;
	int gaussZ;

	uint8_t conf_reg_A;
	uint8_t conf_reg_B;
	uint8_t mode_reg;

	int  convert(int msb_addr, int lsb_addr);
	int  writeI2CDeviceByte(char address, char value);

public:
	HMC5883LMagnetometer(int bus, int address);
	void displayMode(int iterations);

	int  readFullSensorState();
	// The following do physical reads and writes of the sensors
	int setCONF_REG_A(uint8_t desired);
	uint8_t getCONF_REG_A();
	int setCONF_REG_B(uint8_t desired);
	uint8_t getCONF_REG_B();
	int setMODE_REG(uint8_t desired);
	uint8_t getMODE_REG();

	int getGaussX() { return gaussX; }
	int getGaussY() { return gaussY; }
	int getGaussZ() { return gaussZ; }

	virtual ~HMC5883LMagnetometer();
};

#endif /* HMC5883LMAGNETOMETER_H_ */

