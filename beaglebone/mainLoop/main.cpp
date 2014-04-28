#include "control.c"
#include "output.c"
#include "complementary.c"
#include "gps.cpp"
#include "./sensors/ADX345Accelerometer.cpp"
#include "./sensors/L3G4200DGyroscope.cpp"
#include "./sensors/HMC5883LMagnetometer.cpp"
#include "../adsb_decode.h"
#include "write_data.h"
#include "readGPS.h"
#include "serial_write.h"
#include <sys/time.h>
#include <iostream>
#include <string>
#include <stdint.h>
#include <fstream>
using namespace std;


const int    MANUAL    = 1;
const int    AUTONOMOUS= 0;
const double CHECK_GPS = (1/10); // Check the GPS buffer every 10 times per second

int initialize(ADX345Accelerometer &accelerometer, L3G4200DGyroscope &gyroscope, HMC5883LMagnetometer &Magnetometer){
  if (accelerometer.getTIME_FF()!=0x14){
    accelerometer.setTIME_FF(0x14); //100ms free fall interrupt
  }
  if (accelerometer.getDATA_FORMAT()!=0x0a){
    accelerometer.setDATA_FORMAT(0x0a);  //Full resolution +- 8g
  }
  if (accelerometer.getPOWER_CTL()!=0x08){
    accelerometer.setPOWER_CTL(0x08); //Always measure and never sleep
  }
  if (accelerometer.getBW_RATE()!=0x0a){
    accelerometer.setBW_RATE(0x0a);  //0x0a fo 100Hz, 0x0c for 400hz
  }
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
  }
}
int main(){
  int flight_type   = MANUAL;
  int flight_number = 0;
  int num_obstacles  = 0;
  char xbee_port[]  = {"/dev/ttyO4"};
  char data_buf[20] = {'\0'};
  // Clear data.dat
  ofstream fp;
  fp.open("data.dat",fstream::out | fstream::trunc);
  fp.close();

  struct timespec time_count;
  struct termios newtio;
  int fd   = openGPS(&newtio);
  int xbee = open_port(xbee_port);
  uint64_t orig_time;
  struct timeval t1,t2;
  float velocitySetpoint = 10; //intended speed of aircraft
  float obstacleXYZ[3]; //location of obstacle
  float x=0, y=0, z=0; //position
  float vx=0, vy=0, vz=0; //velocities
  float pitch=0, roll=0, yaw=0; //orientation
  float pitchrate=0, rollrate=0, yawrate=0; //orientation rates of change
  float elevator=0, rudder=0, aileron=0, throttle=0; //actuator outputs
  float height=0, heightcommand=0, heightderivative=0; //current height, current desired height, and desired rate of change in height
  int i;
  ADX345Accelerometer accelerometer(1, 0x53);
  L3G4200DGyroscope gyroscope(1,0x69);
  HMC5883LMagnetometer Magnetometer(1,0x1e); //0x1e is the Magnetometer address
  initialize(accelerometer, gyroscope, Magnetometer); //initializes accelerometer, etc.
  int accData[3] = {0,0,0};
  int gyrData[3] = {0,0,0};
  int compData[3]= {0,0,0};
  float time;
  int num_satellites, fixQuality;
  string nmeaSentence;
  float x0=0, y0=0, z0=0;

  //zero GPS
  NMEA("$GPGGA,194459.237,4220.9879,N,07106.3064,W,1,06,1.2,36.6,M,-31.2,M,,0000*59",
       &time, &x0, &y0, &z0, &num_satellites, &fixQuality);
  gettimeofday(&t1,NULL);
  clock_gettime(CLOCK_MONOTONIC,&time_count);
  orig_time = time_count.tv_sec*(uint64_t)1000000000+time_count.tv_nsec;
  while (true){
    //read accelerometer
    accelerometer.readFullSensorState();
    accData[0] = accelerometer.getAccelerationX();
    accData[1] = accelerometer.getAccelerationY();
    accData[2] = accelerometer.getAccelerationZ();
    //read gyroscope
    gyroscope.readFullSensorState();
    gyrData[0] = gyroscope.getAngularRateX();
    gyrData[1] = gyroscope.getAngularRateY();
    gyrData[2] = gyroscope.getAngularRateZ();
    // read magnetometer
    Magnetometer.readFullSensorState();
    compData[0] = Magnetometer.getGaussX();
    compData[1] = Magnetometer.getGaussY();
    compData[2] = Magnetometer.getGaussZ();
    //combine accelerometer and gyroscope, update pitch roll yaw
    complementaryFilter(accData, gyrData, &pitch, &roll, &yaw);
    //    cout << "Pitch:" << pitch << "\tRoll:" << roll << "\n";
    //update pitch roll and yaw rates
    pitchrate = gyrData[1];
    rollrate = gyrData[0];
    yawrate = gyrData[2];
    //read adsb string, get obstacle position
    //get orientation and rates
    imuGET(pitch, roll, yaw, pitchrate, rollrate, yawrate);
    //get desired output (code from simulation)
    heightcommand = getheight(x, obstacleXYZ[0]);
    heightderivative = getheightderivative(x, obstacleXYZ[0]);
    elevator = getelevator(-z, heightcommand, heightderivative, pitch, pitchrate);
    rudder = getrudder(y, yaw); //need constants (set to zero for now)
    aileron = getaileron(roll); //need constants (set to zero for now)
    throttle = getthrottle(vx, velocitySetpoint);
    //stubs to set outputs
    setElevator(elevator);
    setRudder(rudder);
    setAileron(aileron);
    setThrottle(throttle);
    //	cout << "Elevator: " << elevator << "\tRudder: " << rudder << "\tAileron: " << aileron <<"\tThrottle:"<<throttle<<"\n";
    //	cout << "Acc X: " << accData[0] << "\tAcc Y: " << accData[1] << "\tAcc Z: " << accData[2] << "\n";
    clock_gettime(CLOCK_MONOTONIC,&time_count);
    
    // SEND DATA
    char f[4];
    char a[1];
    a[0] = 0xfa;
    write(xbee,a,1);                 // 0xfa
    memcpy(a,&flight_type,1);        // Manual (1) or Auto (0)
    write(xbee,a,1);
    memcpy(a,&flight_number,1);      // Flight number
    write(xbee,a,1);
    memcpy(a,&fixQuality,1);         // GPS Fix Quality
    write(xbee,f,4);
    memcpy(f,&x,4);                  // Longitude
    write(xbee,f,4);
    memcpy(f,&y,4);                  // Latitude
    write(xbee,f,4);
    memcpy(f,&z,4);                  // Altitude
    write(xbee,a,1);
    memcpy(a,&num_satellites,1);     // # of Satellites
    write(xbee,a,1);
    memcpy(a,&num_obstacles,1);      // # of Obstacles

    /*    write_data(time_count.tv_sec*(uint64_t)1000000000+time_count.tv_nsec,
	       time_count.tv_sec*(uint64_t)1000000000+time_count.tv_nsec-orig_time
	       ,"m",
	       x,y,z,
	       roll,pitch,yaw,
	       accData,compData,gyrData,
	       60.7,13.4,fixQuality,num_satellites,0);*/
    orig_time = time_count.tv_sec*(uint64_t)1000000000+time_count.tv_nsec;
    gettimeofday(&t2,NULL);
    if (  t2.tv_sec - t1.tv_sec >= CHECK_GPS ){
      // Reset the initial time
      gettimeofday(&t1,NULL);
      readGPS(fd,&time,&x,&y,&z,&num_satellites,&fixQuality);
    }
  }
}
