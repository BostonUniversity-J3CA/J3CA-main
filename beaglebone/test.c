#include <stdio.h>
#include <math.h>
#include "adsb_decode.h"

int main(int argc, char *argv[]){
  char   adsb[] = {"fa 01 02 0e eb 37 df ff ff ff ff ff ff ff ff 4d 00 e8"};
  double pos[3];
  adsb_decode(adsb,pos);
  printf("%f\n%f\n%f\n",pos[0],pos[1],pos[2]);
  return 0;
}
