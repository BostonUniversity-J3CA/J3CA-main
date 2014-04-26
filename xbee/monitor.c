#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <stdint.h>
#include <dirent.h>
#include <sys/stat.h>

// comment

int open_port(void);
void storePacket(char *buffer, const int checksum);
void setOptions(int *fd, struct termios *options);
int stopRead();
int getFirstDigit(int);

int lines_written = 100;
int fc            = -1;
int folder        = 0;

int main(){
  int fd = open_port();
  // Set all options
  struct termios options;
  
  printf("Reading data...\n");
  setOptions(&fd, &options);
  while ( stopRead() == 0 ){
    // Ready to read!
    char buffer[32];
    char packet[16];
    int  pcount = 0;
    int  i;
    
    // Tracking variables
    int saved_packets = 0;
    int n = read(fd,buffer,sizeof(buffer));
    while ( n > -1 && saved_packets < 20 ) {
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
      n = read(fd,buffer,sizeof(buffer)); 
    }
  }
  // Close the port
  close(fd);
  return 0;
}
void setOptions(int *fd, struct termios *options){
  // Get current options
  tcgetattr(*fd, options);
  // Set BAUD rate
  cfsetispeed(options, B115200);
  cfsetospeed(options, B115200);

  // Enable receiver and set local mode
  (*options).c_cflag |= (CLOCAL | CREAD);

  // Set the character size
  (*options).c_cflag &= ~CSIZE;
  (*options).c_cflag |= CS8;

  // Set raw input
  (*options).c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

  // Set the new options
  tcsetattr(*fd, TCSANOW, options);
}
int stopRead(){
  DIR *dir;
  // Read the command directory
  struct dirent *ent;
  int exists = 0;
  if ( (dir = opendir("../usb/command/")) != NULL ){
    while ( (ent = readdir(dir)) != NULL ){
      if ( strcmp(ent->d_name,"stop") == 0 ){
	exists = 1;
	break;
      }
    }
  }
  closedir(dir);
  return exists;
}
int open_port(void){
  int fd;
  fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
  if ( fd == -1 ){
    perror("open_port: Unable to open /dev/ttyUSB0 \n");
  }
  else
    fcntl(fd, F_SETFL, 0);

  return fd;
}

void storePacket(char *buffer, const int checksum){
  FILE *fp;
  char fname[50];
  char foldername[50];
  sprintf(fname,"../usb/data/%d/%d.dat",folder,fc);
  if ( lines_written == 100 ){
    fc++;
    lines_written = 0;
    if ( fc > 99 )
      folder = getFirstDigit(fc)*100;
    else
      folder = 0;
    
    // Create new folder
    sprintf(foldername,"../usb/data/%d/",folder);
    mkdir(foldername,S_IRGRP | S_IWUSR | S_IRUSR);

    sprintf(fname,"../usb/data/%d/%d.dat",folder,fc);
    fp = fopen(fname,"w+");
    fclose(fp);
  }
  fp = fopen(fname,"a");
  if ( !fp ){
    printf("Could not open file '%s'\n",fname);
    exit(1);
  }
  if ( (checksum & 0xff) != 0xff ){
    // I will log the error properly later
    char error[22];
    sprintf(error,"Checksum error:(%x)",checksum & 0xff);
    //    fwrite(error,1,sizeof(error),fp);
  }
  int i;
  for ( i = 0; i < 16; i++ ){
    fprintf(fp,"%x ",buffer[i] & 0xFF);
  }
  fprintf(fp,"\n");
  lines_written++;
  fclose(fp);
  mode_t perms = 0755;
  chmod(fname,perms);
}
int getFirstDigit(int num){
  int digit = num;
  while ( digit >= 10 )
    digit /= 10;
  return digit;
}
