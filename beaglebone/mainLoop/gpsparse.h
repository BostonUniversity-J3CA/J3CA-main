#include <stdio.h>
#include <math.h>

int NMEA(const char* nmeastring, 
	 float* time, 
	 float* latitude, 
	 float* longitude, 
	 float* altitude, 
	 int* numSatellites, 
	 int* fixQuality)
{
  float hours, minutes, seconds;
  float latminutes, longminutes;
  sscanf(nmeastring, "$GPGGA,%2f%2f%f,%2f%f,N,%3f%f,W,%d,%d,%*f,%f,M,%*f,M%*s", &hours, &minutes, &seconds, latitude, &latminutes, longitude, &longminutes, fixQuality, numSatellites, altitude);
*time = 3600*hours+60*minutes+seconds;
*latitude = (*latitude + latminutes/60)*111080.21226561195; //degrees latitude to m
*longitude = (*longitude + longminutes/60)*82384.58997499943; //degrees longitude to m
//printf("Time: %fs\nLatitude: %fN\nLongitude: %fW\nAltitude: %fm\nFixed?: %d\nNumber of satellites: %d\n", time, latitude, longitude, altitude, fixQuality, numSatellites);
}
