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
int open_port(const char portName[]){
  int fd;
  fd = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);
  if ( fd == -1 ){
    perror("open_port: Unable to open portName \n");
  }
  else
    fcntl(fd, F_SETFL, 0);

  return fd;
}
void readGPS(char buffer[], const char portName[]){
  int fd = open_port(portName);
  // Set all options
  struct termios options;
  
  setOptions(&fd, &options);
  
  int n = read(fd,buffer,sizeof(buffer));
  if ( n < 0 )
    printf("Error: %d",errno);

  // Close the port
  close(fd);
}
