#include <stdio.h>
#include <math.h>
#include "adsb_decode.h"

int main(int argc, char *argv[]){
  char  adsb[] = {"fa 1 2 f8 ee c2 fb 9b 31 86 2 50 d2 95 1 4d 0 e8"};
  float pos[3];
  adsb_decode(adsb,pos);
  printf("%f\n%f\n%f\n",pos[0],pos[1],pos[2]);
  return 0;
}
