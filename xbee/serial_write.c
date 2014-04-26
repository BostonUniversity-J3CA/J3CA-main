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

// comment

int open_port(void);
void writePacket(char *buffer);
void setOptions(int *fd, struct termios *options);
int stopRead();
int getFirstDigit(int);

int main(int argc, char *argv[]){
  char buffer[52];
  int fd = open_port();
  // Set all options
  struct termios options;
  
  setOptions(&fd, &options);

  writePacket(buffer);
  printf("Sending packets\n");
  while ( access("./usb/command/stop",F_OK) == -1 ) {
    // Now send the packet to the XBEE
    if ( write(fd,buffer,sizeof(buffer)) < 0 ){
      fputs("Error sending packet to XBEE!\n",stderr);
      exit(1);
    }
    sleep(1);
  }
  
  // Close the port
  close(fd);
  return 0;
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
int stopRead(){
  DIR *dir;
  // Read the command directory
  struct dirent *ent;
  int exists = 0;
  if ( (dir = opendir("../usb/command/")) != NULL ){
    while ( (ent = readdir(dir)) != NULL ){
      if ( strcmp(ent->d_name,"stop") == 0 ){
	exists = 1;
	break;
      }
    }
  }
  closedir(dir);
  return exists;
}
int open_port(void){
  int fd;
  fd = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY | O_NDELAY);
  if ( fd == -1 ){
    perror("open_port: Unable to open /dev/ttyUSB1 \n");
  }
  else
    fcntl(fd, F_SETFL, 0);

  return fd;
}

void writePacket(char *buffer){
  sprintf(buffer,"fa 1 2 f8 ee c2 fb 9b 31 86 2 50 d2 95 1 4d 0 e8");
}
