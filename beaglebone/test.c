#include <stdio.h>
#include <string.h>
#include "readGPS.h"

int main(int argc, char *argv[]){
  char buffer[76];
  char output[76];
  int count = 0;

  while ( count < 50 && strlen(output) < 75 ){
    readGPS(buffer,"/dev/tty01");
    strcat(output,buffer);
    count++;
  }
  printf("%s\n",output);
  return 0;
}
