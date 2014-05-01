/*
 * GPS.cpp
 *
 *  Created on: Apr 30, 2014
 *      Author: John, L. Gillespie, John R. Aleman, Joseph E. Stone, Chirag Rathod, Ari J. Morse
 *      College of Engineering, Boston University
 *      Notes: Parses a GPGGA sentence into numbers
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

#include <stdio.h>
#include <math.h>
#include <string>
using namespace std;

int NMEA(const char nmeaSentence[], float* x, float* y, float* altitude, int* numSatellites, int* fixQuality)
{
float hours, minutes, seconds;
float latitude, longitude;
float latminutes, longminutes;
//string nmeaSentence = "$GPGGA,194459.236,4220.9878,N,07106.3063,W,1,06,1.2,36.5,M,-31.2,M,,0000*59";
sscanf(nmeaSentence, "$GPGGA,%2f%2f%f,%2f%f,N,%3f%f,W,%d,%d,%*f,%f,M,%*f,M%*s", &hours, &minutes, &seconds, &latitude, &latminutes, &longitude, &longminutes, fixQuality, numSatellites, altitude);
//*time = 3600*hours+60*minutes+seconds;
*x = (latitude + latminutes/60)*111080.21226561195; //degrees latitude to m
*y = (longitude + longminutes/60)*82384.58997499943; //degrees longitude to m
}
