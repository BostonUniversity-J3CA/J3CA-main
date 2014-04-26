#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <stdint.h>

void adsb_decode(const char packet[], double obs_pos[]){
  char buffer[32];
  int  pcount = 0;
  int  i;
  
  // Tracking variables
  int checksum = 0;
  int begin = 0;
  for (i = 0; i < 32; i++){
    if ( begin == 0 ){
      if ( (buffer[i] & 0xff) == 0xfa )
	begin = 1;
    }
    else {
      if ( (buffer[i] & 0xff) != 0xfa ){
	checksum += buffer[i];
	packet[pcount] = buffer[i];	  
	pcount++;
	if ( pcount == 16 ){
	  // The packet is full and we haven't reached the delimiter yet...an error has occurred! Discard the packet
	  pcount = 0;
	}
      }
      else {
	// Is this the end of a pack?
	if ( pcount < 15 ){
	  // Nope
	  packet[pcount] = buffer[i];
	  pcount++;
	}
	else {
	  storePacket(packet,checksum);
	  saved_packets++;
	  pcount = 0;
	  begin = 0;
	}   
      }
    }
  }
}
  
