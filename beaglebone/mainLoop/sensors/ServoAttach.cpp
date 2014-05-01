/*
 * ServoAttach.cpp
 *  Created on: Apr 29, 2014
 *      Author: John R. Aleman, College of Engineering, Boston University
 *      Notes: This Definition of a class to interface with the
 *      Analog Devices ADXL345 Digital Accelerometer was created based
 *      on the work of Derek Molloy.
 *      Copyright John R. ALeman, College of Engineering, Boston University
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

#include <iostream>
#include "ServoAttach.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sstream>

using namespace std;

ServoAttach::ServoAttach(char address[64]) {
	snprintf(pwmDir, sizeof(pwmDir), "%s" ,address);
}

int ServoAttach::setDuty(int desired){
	int fd;
	char buf[64];
	snprintf(buf, sizeof(buf), "%s/duty", this->pwmDir);
	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("Failed to open duty");
		return fd;
	}
    char value[64] = "";
    snprintf(value,sizeof(value),"%d",desired);
	if(write(fd, value, sizeof(value)) < 1){
		cout << "Failure to set duty" << endl;
		return 1;
	}
	close(fd);

	return 0;
}

int ServoAttach::setPeriod(int desired){
	int fd;
	char buf[64];
	snprintf(buf, sizeof(buf), "%s/period", this->pwmDir);
	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("Failed to open period");
		return fd;
	}
    char value[64] = "";
    snprintf(value,sizeof(value),"%d",desired);
	if(write(fd, value, sizeof(value)) < 1){
		cout << "Failure to set period" << endl;
		return 1;
	}
	close(fd);

	return 0;
}

int ServoAttach::setPolarity(int desired){
	int fd;
	char buf[64];
	snprintf(buf, sizeof(buf), "%s/polarity", this->pwmDir);
	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("Failed to open polarity");
		return fd;
	}
    char value[64] = "";
    snprintf(value,sizeof(value),"%d",desired);
	if(write(fd, value, sizeof(value)) < 1){
		cout << "Failure to set polarity" << endl;
		return 1;
	}
	close(fd);

	return 0;
}

int ServoAttach::setRun(int desired){
	int fd;
	char buf[64];
	snprintf(buf, sizeof(buf), "%s/run", this->pwmDir);
	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("Failed to open run");
		return fd;
	}
    char value[64] = "";
    snprintf(value,sizeof(value),"%d",desired);
	if(write(fd, value, sizeof(value)) < 1){
		cout << "Failure to set run" << endl;
		return 1;
	}
	close(fd);

	return 0;
}




ServoAttach::~ServoAttach() {
	// TODO Auto-generated destructor stub
}

