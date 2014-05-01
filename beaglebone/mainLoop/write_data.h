/*
 * write_data.h
 *
 *  Created on: Apr 30, 2014
 *      Author: John, L, Gillespie, John R. Aleman, Joseph E. Stone, Chirag Rathod, Ari J. Morse
 *      College of Engineering, Boston University
 *      Notes: Writes sensor data to a new file for every test. 
 *      Copyright G.R.A.M.S., College of Engineering, Boston University
 *      jaleman@bu.edu, chiragr314@gmail.com, johngillespie27@yahoo.com, jestone@bu.edu, amorse@bu.edu
 *
 * 		Redistribution and use in source and binary forms, with or without modification,
 * 		are permitted provided that the following conditions are met:
 * 			1. Redistributions of source code must retain the above copyright
 *    			notice, this list of conditions and the following disclaimer.
 * 			2. Redistributions in binary form must reproduce the above copyright
 *    			notice, this list of conditions and the following disclaimer in the
 *    			documentation and/or other materials provided with the distribution.
 *
 * 		THIS SOFTWARE IS PROVIDED ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * 		INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * 		AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL I
 * 		BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * 		CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * 		GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * 		HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * 		OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * 		SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */



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
