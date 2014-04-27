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
#include <sys/ioctl.h>

int open_port(void);
void storePacket(char *buffer);
void setOptions(int *fd, struct termios *options);
int stopRead();
int getFirstDigit(int);

int lines_written = 100;
int fc            = -1;
int folder        = 0;

int main(int argc, char *argv[]){
  int fd = open_port();
  // Set all options
  struct termios options;

  printf("Reading data...\n");
  setOptions(&fd, &options);

  // Ready to read!

  int  bytes = 0;
  char buffer[2];
  int  pcount = 0;
  char temp[2];
  char packet[32] = {0};
  int  checksum = 0;
  int  begin    = 0;
  while ( stopRead() == 0 ){    
    // Tracking variables
    ioctl(fd,FIONREAD,&bytes);
    
    if ( bytes > 0 ){
      if ( read(fd, buffer, sizeof(buffer)) > 0 ){
	if ( begin == 1 ){
	  if ( buffer[0] == 0xfa )
	    begin = 1;
	}
	else {
	  checksum += buffer[0];
	  sprintf(temp,"%x",buffer[0]);
	  strcat(packet,temp);
	  strcat(packet," ");
	  pcount++;
	  if ( pcount == 16 ){
	    printf("%s\n",packet);
	    exit(1);
	    if ( checksum == 0xff ){
	      storePacket(packet);
	    }
	    else {
	      printf("checksum error!: %x\n",checksum);
	      exit(1);
	    }
	    memset(packet,'\0',16);
	    pcount = 0;
	    begin = 0;
	  }
	}
      }
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
  fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
  if ( fd == -1 ){
    perror("open_port: Unable to open /dev/ttyUSB0 \n");
  }
  else
    fcntl(fd, F_SETFL, 0);

  return fd;
}

void storePacket(char *buffer){
  FILE *fp;
  char fname[50];
  char foldername[50];
  sprintf(fname,"../usb/data/%d/%d.dat",folder,fc);
  if ( lines_written == 100 ){
    fc++;
    lines_written = 0;
    if ( fc % 100 == 0 )
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
  fprintf(fp,"%s\n",buffer);
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
