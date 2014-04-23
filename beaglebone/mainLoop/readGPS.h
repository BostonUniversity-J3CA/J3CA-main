#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyO1"
#define _POSIX_SOURCE 1

#define FALSE 0
#define TRUE 1

int readGPS(int fd, 
	    float* time, 
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
    NMEA(buf,time,latitude,longitude,altitude,numSatellites,fixQuality);
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
