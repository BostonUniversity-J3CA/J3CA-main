/*
 * Complimentary Filter.c
 *
 *
 *  Created on: Apr 30, 2014
 *      Author: John, L, Gillespie, John R. Aleman, Joseph E. Stone, Chirag Rathod, Ari J. Morse
 *      College of Engineering, Boston University
 *      Notes: Sensor fusion usign the complimentary filter
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



#include <sys/time.h>
#define GYRO_SENS .00762939453 //rad/s per bit
#define PI 3.14159265359
#define FRACTIONACC .02

void complementaryFilter(int accData[3], int gyrData[3], float* pitch, float* roll, float* yaw)
{
	static struct timeval last;
	static bool flag = false;
	if (!flag)
	{
		gettimeofday(&last, NULL);
	}
	struct timeval now;
	gettimeofday(&now, NULL);
	float dt = ((now.tv_sec-last.tv_sec) + (now.tv_usec - last.tv_usec)/1000000.);
	last = now;
	flag = true;
	float pitchAcc, rollAcc;
	*pitch += ((float)gyrData[1] * GYRO_SENS) * dt;
	*roll += ((float)gyrData[0] * GYRO_SENS) * dt;
	*yaw += ((float)gyrData[2] * GYRO_SENS) * dt;
	pitchAcc = atan2f((float)accData[0], (float)accData[2]) * 180 / PI;
	*pitch = *pitch * (1-FRACTIONACC) + pitchAcc * FRACTIONACC;
	rollAcc = -atan2f((float)accData[1], (float)accData[2]) * 180 / PI;
	*roll = *roll * (1-FRACTIONACC) + rollAcc * FRACTIONACC;
}
