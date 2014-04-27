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
#include <sys/ioctl.h>
#include "serial_write.h"

void storePacket(char *buffer, const int checksum);
int stopRead();

int lines_written = 100;
int fc            = -1;
int folder        = 0;

int main(int argc, char *argv[]){
  int fd = open_port();

  printf("Writing data...\n");
  
  int test[] = {250,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250};
  // Ready to read!
  while ( 1 ){
    send(fd,test,16);
    sleep(1);
  }
  close(fd);
  return 0;
}


