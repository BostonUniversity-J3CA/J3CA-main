#ifndef ADSB_DECODE_H
#define ADSB_DECODE_H

#include <stdio.h>
#include <string.h>
#include <math.h>

double hex_to_int(const char hex[]){
  // This function takes a character array representing a hexadecimal number and returns the decimal equivalent
  int    SIZE= strlen(hex);
  int    i   = 0;
  double sum = 0;
  int    n   = 0;
  int    expn= 0;
  for ( i = SIZE-1; i > -1; i--, expn++ ){
    if ( hex[i] != ' ' ){
      switch (hex[i]){
      case 'a':
	n = 10;
	break;
      case 'b':
	n = 11;
	break;
      case 'c':
	n = 12;
      break;
      case 'd':
	n = 13;
	break;
      case 'e':
	n = 14;
	break;
      case 'f':
	n = 15;
	break;
      default:
	n = hex[i]-'0';
      }
      sum += n*pow(16,expn);
    }
  }
  return sum;
}

int adsb_decode(const char adsb[], double* obs_pos){
  // The function takes an adbs string (character array) and returns a pointer to an array of 3 floats defining the 
  // obstacles latitude, longitude, and altitude position in degrees

  int  i, n;       // For loop variables
  char hex[8];     // Character array representing the hex for the obstacle's position
  int  index  = 0; // The current index in the hex array
  int  o      = 0; // The current index in the obs_pos array
  int  count  = 0; // Counts the number of spaces
  
  // Latitude
  hex[0] = adsb[9];
  hex[1] = adsb[10];
  hex[2] = adsb[12];
  hex[3] = adsb[13];
  hex[4] = adsb[15];
  hex[5] = adsb[16];
  hex[6] = adsb[18];
  hex[7] = adsb[19];

  obs_pos[0] = hex_to_int(hex);

  // Longitude

  hex[0] = adsb[21];
  hex[1] = adsb[22];
  hex[2] = adsb[24];
  hex[3] = adsb[25];
  hex[4] = adsb[27];
  hex[5] = adsb[28];
  hex[6] = adsb[30];
  hex[7] = adsb[31];

  obs_pos[1] = hex_to_int(hex);

  // Longitude

  hex[0] = adsb[33];
  hex[1] = adsb[34];
  hex[2] = adsb[36];
  hex[3] = adsb[37];
  hex[4] = adsb[39];
  hex[5] = adsb[40];
  hex[6] = adsb[42];
  hex[7] = adsb[43];

  obs_pos[2] = hex_to_int(hex);
  
  return 1;
}
#endif
