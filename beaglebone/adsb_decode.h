#ifndef ADSB_DECODE_H
#define ADSB_DECODE_H

#include <stdio.h>
#include <string.h>
#include <math.h>

float hex_to_int(const char hex[]){
  // This function takes a character array representing a hexadecimal number and returns the decimal equivalent
  int SIZE= strlen(hex);
  int i   = 0;
  int sum = 0;
  int n   = 0;
  int expn= 0;
  for ( i = SIZE-1; i > -1; i--, expn++ ){
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
  return sum;
}

float* adsb_decode(const char adsb[]){
  // The function takes an adbs string (character array) and returns a pointer to an array of 3 floats defining the 
  // obstacles latitude, longitude, and altitude position in degrees
  static float obs_pos[3];
  int i, n; // For loop variables
  char hex[9]; // Character array representing the hex for the obstacle's position
  int index = 0; // The current index in the hex array
  int o     = 0; // The current index in the obs_pos array
  for ( i = 0, n = strlen(adsb); i < n; i++ ){
    if ( i > 1 && i < 25 ){
      hex[index] = adsb[i];
      index++;
      if ( index == 8 && o < 3 ){
	obs_pos[o] = hex_to_int(hex);
	o++;
	index = 0;
      }
    }
  }
  return obs_pos;
}
#endif
