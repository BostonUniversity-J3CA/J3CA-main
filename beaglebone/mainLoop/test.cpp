#include <iostream>
#include <stdint.h>
#include <inttypes.h>
#include <fstream>
#include <cstdio>
#include "/home/ubuntu/J3CA-main/beaglebone/mainLoop/control.c"
#include "/home/ubuntu/J3CA-main/beaglebone/mainLoop/output.c"
#include "/home/ubuntu/J3CA-main/beaglebone/mainLoop/complementary.c"
#include "/home/ubuntu/J3CA-main/beaglebone/mainLoop/readGPS.h"
#include "/home/ubuntu/J3CA-main/beaglebone/mainLoop/gpsparse.c"
#include "/home/ubuntu/J3CA-main/beaglebone/mainLoop/imu.cpp"
#include <sys/time.h>
#include <unistd.h>
//#include "/home/ubuntu/J3CA-main/beaglebone/mainLoop/sensors/ADX345Accelerometer.cpp"
//#include "/home/ubuntu/J3CA-main/beaglebone/mainLoop/sensors/L3G4200DGyroscope.cpp"
//#include "./sensors/ADX345Accelerometer.cpp"
//#include "./sensors/L3G4200DGyroscope.cpp"
//#include "/home/ubuntu/J3CA-main/beaglebone/mainLoop/sensors/HMC5883LMagnetometer.cpp"
#include "/home/ubuntu/J3CA-main/beaglebone/mainLoop/readGPS.h"
#include "../write_data.h"
using namespace std;

int main(int argc, char *argv[]){
  //L3G4200DGyroscope gyroscope(1,0x69);
  //ADX345Accelerometer accelerometer(1, 0x53);

  //HMC5883LMagnetometer Magnetometer(1,0x1e); //0x1e is the Magnetometer address
  int acc[] = {0,0,0};
  int compass[] = {0,2,1};
  int gyro[] = {0,0,4};
  float x = 0, y = 0, z = 0;
  int numSatellites;
  int fixQuality;
  uint64_t orig_time;
  uint64_t dtime = 0.0;
  struct timespec time;
  struct termios newtio;
  float time_d;

  int fd = openGPS(&newtio);
  // Initialize accelerometer
  /*if (accelerometer.getTIME_FF()!=0x14){
    accelerometer.setTIME_FF(0x14); //100ms free fall interrupt
    }
    if (accelerometer.getDATA_FORMAT()!=0x0a){
    accelerometer.setDATA_FORMAT(0x0a);  //Full resolution +- 8g
    }
    if (accelerometer.getPOWER_CTL()!=0x08){
    accelerometer.setPOWER_CTL(0x08); //Always measure and never sleep
    }
    if (accelerometer.getBW_RATE()!=0x0c){
    accelerometer.setBW_RATE(0x0c);  //0x0a fo 100Hz, 0x0c for 400hz
    }
 
    // Initialize the gyroscope
    if (gyroscope.getCTRL_REG1()!=0x0f){
    gyroscope.setCTRL_REG1(0x0f); //Enables three axis and sets 100hz
    }
    if (gyroscope.getCTRL_REG2()!=0x20){
    gyroscope.setCTRL_REG2(0x20); //Normal mode no high Pass
    }
    if (gyroscope.getCTRL_REG3()!=0x00){
    gyroscope.setCTRL_REG3(0x00); //FIFO and interrupt configuration
    }
    if (gyroscope.getCTRL_REG4()!=0x00){
    gyroscope.setCTRL_REG4(0x00); //Data format and bus selection
    }
    if (gyroscope.getCTRL_REG5()!=0x00){
    gyroscope.setCTRL_REG5(0x00); //FIFO and interrupt enable
    }
    
    // Initialize magnetometer
    if (Magnetometer.getCONF_REG_A()!=0x18){
    Magnetometer.setCONF_REG_A(0x18); //Data Rate and data averaging
    }
    
    if (Magnetometer.getCONF_REG_B()!=0x20){
    Magnetometer.setCONF_REG_B(0x20); //Gain
    }
    
    if (Magnetometer.getMODE_REG()!=0x00){
    Magnetometer.setMODE_REG(0x00); //Continious Mode
    }*/
 
  // Clear file
  ofstream fp;
  fp.open("data.dat",ofstream::out | ofstream::trunc);
  fp.close();

  clock_gettime(CLOCK_MONOTONIC, &time);
  orig_time = time.tv_sec*(uint64_t)1000000000+time.tv_nsec;
  
  
  while (1){  
    /*accelerometer.readFullSensorState();
    acc[0] = accelerometer.getAccelerationX();
    acc[1] = accelerometer.getAccelerationY();
    acc[2] = accelerometer.getAccelerationZ();

    gyroscope.readFullSensorState();
    gyro[0] = gyroscope.getAngularRateX();
    gyro[1] = gyroscope.getAngularRateY();
    gyro[2] = gyroscope.getAngularRateZ();

    Magnetometer.readFullSensorState();
    compass[0] = Magnetometer.getGaussX();
    compass[1] = Magnetometer.getGaussY();
    compass[2] = Magnetometer.getGaussZ();*/

    readGPS(fd,&time_d,&x,&y,&z,&numSatellites,&fixQuality);
    
    write_data(orig_time, dtime, "a",x,y,z,1.54,23.545,11.45,acc,compass,gyro,68.4,30.5,fixQuality,numSatellites,0);
    usleep(2000);
    clock_gettime(CLOCK_MONOTONIC, &time);
    dtime = (time.tv_sec*(uint64_t)1000000000+time.tv_nsec) - orig_time;
    orig_time = time.tv_sec*(uint64_t)1000000000+time.tv_nsec;
  }
  return 1;
}
