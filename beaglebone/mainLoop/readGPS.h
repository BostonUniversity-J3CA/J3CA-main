/*
 * ReadGPS.h
 
 *  Created on: Apr 30, 2014
 *      Author: John, L, Gillespie, John R. Aleman, Joseph E. Stone, Chirag Rathod, Ari J. Morse
 *      College of Engineering, Boston University
 *      Notes: Reads the GPS data
 *      Copyright G.R.A.M.S., College of Engineering, Boston University
 *      jaleman@bu.edu, chiragr314@gmail.com, johngillespie27@yahoo.com, jestone@bu.edu, amorse@bu.edu
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



#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyO1"
#define _POSIX_SOURCE 1

#define FALSE 0
#define TRUE 1

int readGPS(int fd, 
	    float* latitude, 
	    float* longitude, 
	    float* altitude, 
	    int* numSatellites, 
	    int* fixQuality){
  int res;
  char buf[255];
  res = read(fd,buf,255);
  buf[res] = 0;
  if ( strlen(buf) >= 75 ){
    NMEA(buf,latitude,longitude,altitude,numSatellites,fixQuality);
    return 1;
  }
  return 0;
}

int openGPS(struct termios *newtio){
  int fd;
  fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY | O_NDELAY);
  if ( fd < 0 ){
    perror(MODEMDEVICE);
    exit(-1);
  }
  (*newtio).c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
  (*newtio).c_iflag = IGNPAR;
  (*newtio).c_oflag = 0;
  
  (*newtio).c_lflag = ICANON;
  tcflush(fd,TCIFLUSH);
  tcsetattr(fd,TCSANOW,newtio);
  
  return fd;
}
