/*
 * ServoAttach.h
 *
 *  Created on: Apr 29, 2014
 *      Author: jaleman
 */

#ifndef SERVOATTACH_H_
#define SERVOATTACH_H_

class ServoAttach {
private:
	char pwmDir[64];

public:
	ServoAttach(char address[64]);
	void displayMode(int iterations);
	// The following do physical reads and writes of the sensors
	int setDuty(int desired);
	int setPeriod(int desired);
	int setPolarity(int desired);
	int setRun(int desired);

	virtual ~ServoAttach();
};

#endif /* SERVOATTACH_H_ */
