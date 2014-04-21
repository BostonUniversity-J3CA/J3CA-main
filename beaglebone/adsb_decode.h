#ifndef ADSB_DECODE_H
#define ADSB_DECODE_H

#include <stdio.h>
#include <string.h>
#include <math.h>

float hex_to_int(const char hex[]){
  // This function takes a character array representing a hexadecimal number and returns the decimal equivalent
  int   SIZE= strlen(hex);
  int   i   = 0;
  float sum = 0;
  int   n   = 0;
  int   expn= 0;
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

int adsb_decode(const char adsb[], float* obs_pos){
  // The function takes an adbs string (character array) and returns a pointer to an array of 3 floats defining the 
  // obstacles latitude, longitude, and altitude position in degrees

  int i, n; // For loop variables
  char hex[9]; // Character array representing the hex for the obstacle's position
  int index = 0; // The current index in the hex array
  int o     = 0; // The current index in the obs_pos array
  int count = 0; // Counts the number of spaces
  for ( i = 7, n = strlen(adsb); i < n; i++ ){
    if ( adsb[i] != ' ' ){
      hex[index] = adsb[i];
      index++;
    }
    else {
      count++;
      if ( count == 4 ){
	index = 0;
	count = 0;
	obs_pos[o] = hex_to_int(hex);
	o++;
	if ( o == 3 )
	  break;
      }
    }
  }
  return 1;
}
#endif
