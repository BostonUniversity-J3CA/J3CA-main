#ifndef WRITE_DATA_H
#define WRITE_DATA_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdint.h>
#include <inttypes.h>
#include <sstream>
#include <unistd.h>

using namespace std;
char fname[50] = {"/home/ubuntu/dataFiles/data0.dat"};
//char fname[80] = {"/home/john/Programs/seniordesign/beaglebone/mainLoop/data0.dat"};
ofstream file;

void make_file_name(){
	// Find the next file name to use
	int i = 1;
	sprintf(fname,"/home/ubuntu/dataFiles/data%d.dat",i);
//	sprintf(fname,"/home/john/Programs/seniordesign/beaglebone/mainLoop/data%d.dat",i);
	while ( 	access(fname,F_OK) != -1 ){
	  i++;
	  sprintf(fname,"/home/ubuntu/dataFiles/data%d.dat",i);
//	  sprintf(fname,"/home/john/Programs/seniordesign/beaglebone/mainLoop/data%d.dat",i);
	}
}


int write_data(const int time,
	       const int dtime,
	       const char *mode,
	       const float lon,
	       const float lat,
	       const float alt,
	       const float roll,
	       const float pitch,
	       const float yaw,
	       const int acc[],
	       const int compass[],
	       const int gyro[],
	       const double temp,
	       const double pressure,
	       const int gps_fix,
	       const int nsat,
	       const int nobs){
  ostringstream  t, dt;
  t  << time;
  dt << dtime;
  //file.open(fname,fstream::app);
  file << t.str() << " " << dt.str() << " " <<  mode << " " <<  lon << " "
       << lat << " " << alt << " " << roll << " " <<  pitch << " "
       << yaw << " " << acc[0] << " " << acc[1] << " " << acc[2]
       << " " << compass[0] << " " << compass[1] << " " << compass[2]
       << " " << gyro[0] << " " << gyro[1] << " " << gyro[2] << " "<< temp
       << " " << pressure << " " << gps_fix << " " << nsat << " "
       << nobs << endl;
  //file.close();
  return 0;
}
#endif
