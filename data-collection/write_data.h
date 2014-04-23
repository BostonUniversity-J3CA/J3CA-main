#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int write_data(const double time,
	       const char mode,
	       const double lon,
	       const double lat,
	       const double alt,
	       const double roll,
	       const double pitch,
	       const double yaw,
	       const double acc[],
	       const double compass[],
	       const double gyro[],
	       const double temp,
	       const double pressure,
	       const int gps_fix,
	       const int nsat,
	       const int nobs){
  FILE *fp = fopen("data.dat","a");
  if ( !fp ){
    printf("Could not open or create 'data.dat'");
    return -1;
  }
  else {
    fprintf(fp,"%f %c %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %d %d\n",
	       time, mode, 
	       lon, lat, alt,
	       roll, pitch, yaw,
	       acc[0], acc[1], acc[2],
	       compass[0], compass[1], compass[2],
	       gyro[0], gyro[1], gyro[2],
	       temp, pressure, gps_fix, nsat, nobs);
  }
  return 0;
}
