/*
 * ServoAttach.cpp
 *
 *  Created on: Apr 29, 2014
 *      Author: jaleman
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

