#include <stdio.h>
#include <math.h>
#include <string>
using namespace std;

int gpsRead(float* time, float* x, float* y, float* altitude, int* numSatellites, int* fixQuality)
{
float hours, minutes, seconds;
float latitude, longitude;
float latminutes, longminutes;
string nmeaSentence = "$GPGGA,194459.236,4220.9878,N,07106.3063,W,1,06,1.2,36.5,M,-31.2,M,,0000*59";
sscanf(nmeaSentence.c_str(), "$GPGGA,%2f%2f%f,%2f%f,N,%3f%f,W,%d,%d,%*f,%f,M,%*f,M%*s", &hours, &minutes, &seconds, &latitude, &latminutes, &longitude, &longminutes, fixQuality, numSatellites, altitude);
*time = 3600*hours+60*minutes+seconds;
*x = (latitude + latminutes/60)*111080.21226561195; //degrees latitude to m
*y = (longitude + longminutes/60)*82384.58997499943; //degrees longitude to m
//printf("Time: %fs\nLatitude: %fN\nLongitude: %fW\nAltitude: %fm\nFixed?: %d\nNumber of satellites: %d\n", time, latitude, longitude, altitude, fixQuality, numSatellites);
}
