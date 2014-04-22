#include <stdio.h>
#include <string.h>
#include "readGPS.h"

int main(int argc, char *argv[]){
  char buffer[150];
  buffer[0] = 0;
  int count = 0;

  while ( count < 150 ){
    printf("reading...\n");
    readGPS(buffer,"/dev/ttyUSB0");
    count++;
  }
  printf("%s\n",buffer);
  return 0;
}
