#ifndef XBEE_SEND_H
#define XBEE_SEND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <stdint.h>
#include <dirent.h>
#include <sys/stat.h>

void send(const int fd, const int buf[], const int buf_size){
  int i = 0;
  int a[1];
  for ( i = 0; i < buf_size; i++ ){
    a[0] = buf[i];
    write(fd, a, 1);
  }
}
void setOptions(int *fd, struct termios *options){
  // Get current options
  tcgetattr(*fd, options);
  // Set BAUD rate
  cfsetispeed(options, B115200);
  cfsetospeed(options, B115200);

  // Enable receiver and set local mode
  (*options).c_cflag |= (CLOCAL | CREAD);

  // Set the character size
  (*options).c_cflag &= ~CSIZE;
  (*options).c_cflag |= CS8;

  // Set raw input
  (*options).c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

  // Set the new options
  tcsetattr(*fd, TCSANOW, options);
}
int open_port(char portName[]){
  int fd;
  struct termios options;

  fd = open(portName, O_RDWR | O_NOCTTY);
  if ( fd == -1 ){
    printf("open_port: Unable to open %s \n",portName);
  }
  else
    fcntl(fd, F_SETFL, 0);
  
  setOptions(&fd, &options);
  return fd;
}

#endif
