#include <sys/time.h>
#define GYRO_SENS .00013315805 //rad/s per bit
#define PI 3.14159265359

void complementaryFilter(int accData[3], int gyrData[3], float* pitch, float* roll)
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
	*pitch += ((float)gyrData[0] * GYRO_SENS) * dt;
	*roll += ((float)gyrData[1] * GYRO_SENS) * dt;
	pitchAcc = atan2f((float)accData[1], (float)accData[2]) * 180 / PI;
	*pitch = *pitch * .98 + pitchAcc * .02;
	rollAcc = atan2f((float)accData[0], (float)accData[2]) * 180 / PI;
	*roll = *roll * .98 + rollAcc * .02;
}
