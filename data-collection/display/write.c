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
#include <math.h>
#include "/home/stone-joe/Downloads/Programming/SeniorDesignCode/J3CA-main/beaglebone/adsb_decode.h"
#include "serial_write.h"
#include <unistd.h>

void storePacket(char *buffer, const int checksum);
int stopRead();

int main(int argc, char *argv[]){
  int fd = open_port("/dev/ttyUSB1");

  printf("Writing data...\n");
  
  char a[1];
  char f[4];

  // Start flag
  int i         = 250;
  int manual    = 0;
  int gps_fix   = 1;
  int flight_id = 0;
  float       x = 82.612;
  float       y = 34.975;
  float       z = 30.789;
  int num_sat   = 6;
  int num_obs   = 0;
  int c         = 0;
  int checksum  = 0;
  char packet[18] = {'\0'};

  // Ready to write!
  while ( 1 ){
    checksum = 0;
    // Send flag
    memcpy(a,&i,1);
    write(fd,a,1);
    // Send flight type (manual or autonomous)
    memcpy(a,&manual,1);
    write(fd,a,1);
    checksum += a[0];
    // Send GPS fix
    memcpy(a,&gps_fix,1);
    write(fd,a,1);
    checksum += a[0];
    // Send Flight id
    memcpy(a,&flight_id,1);
    write(fd,a,1);
    checksum += a[0];
    // Send x data
    memcpy(f,&x,4);
    write(fd,f,4);
    checksum += f[0]+f[1]+f[2]+f[3];
    // Send y data
    memcpy(f,&y,4);
    write(fd,f,4);
    checksum += f[0]+f[1]+f[2]+f[3];
    // Send z data
    memcpy(f,&z,4);
    write(fd,f,4);
    checksum += f[0]+f[1]+f[2]+f[3];
    // Send satellite data
    memcpy(a,&num_sat,1);
    write(fd,a,1);
    checksum += a[0];
    // Send obstacle data
    memcpy(a,&num_obs,1);
    write(fd,a,1);
    checksum += a[0];
    // Send checksum
    memcpy(a,&checksum,1);
    write(fd,a,1);

    printf("%d\n",checksum);
    
    sleep(1);
  }
  close(fd);
  return 0;
}
