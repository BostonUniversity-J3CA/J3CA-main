#include "control.c"
#include "output.c"
#include "complementary.c"
#include "gpsparse.c"
#include "imu.cpp"
#include "../adsb_decode.h"
#include "./sensors/ADX345Accelerometer.cpp"
#include "./sensors/L3G4200DGyroscope.cpp"
#include "write_data.h"
#include "readGPS.h"
#include <sys/time.h>
#include <iostream>
#include <string>
#include <stdint.h>

using namespace std;

int main(int argc, char *argv[]){
  float x=0,y=0,z=0;
  float time=0;
  int numSats=0;
  int fixQual=0;
  struct termios newtio;
  int fd = openGPS(&newtio);

  while (1){
    readGPS(fd,&time,&x,&y,&z,&numSats,&fixQual);
  }
  return 0;
}
