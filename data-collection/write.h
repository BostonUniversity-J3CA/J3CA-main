#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int write_to_file(const float numbers[], const int size, const char* filename){
  FILE *f;
  const int str_size = size*2;
  f = fopen(filename, "a+");
  if ( f == NULL )
    return 0; 
  else {
    int i = 0;
    for ( i; i < size; i++ ){
      if ( i != size-1 )
	fprintf(f,"%.3g\t",numbers[i]);
      else
	fprintf(f,"%.3g\n",numbers[i]);
    }
  }
  fclose(f);
  return 1;
}
int write_string_to_file(const char string[], const char* filename, const int overwrite){
  FILE *f;
  if ( overwrite == 1 )
    f = fopen(filename,"w+");
  else
    f = fopen(filename,"a+");

  if ( f == NULL ){
    printf("Could not open file: '%s'\n",filename);
    return -1;
  }
  else {
    fprintf(f,"%s",string);
  } 
  fclose(f);
  return 1;
}
