#ifndef WRITE_DATA_H
#define WRITE_DATA_H

#include <iostream>
#include <fstream>

using namespace std;

int write_data(const float time,
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
  ofstream file;
  file.open("data.dat",fstream::app);
  if ( !file.good() )
    file.open("data.dat");
  file << time << " " <<  mode << " " <<  lon << " "
       << lat << " " << alt << " " << roll << " " <<  pitch << " "
       << yaw << " " << acc[0] << " " << acc[1] << " " << acc[2]
       << " " << compass[0] << " " << compass[1] << " " << compass[2]
       << " " << gyro[0] << " " << gyro[1] << " " << gyro[2] << temp
       << " " << pressure << " " << gps_fix << " " << nsat << " "
       << nobs << endl;
  file.close();
  return 0;
}
#endif
