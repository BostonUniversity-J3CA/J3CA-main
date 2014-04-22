#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyUSB0"
#define _POSIX_SOURCE 1

#define FALSE 0
#define TRUE 1

int main(int argc, char *argv[]){
	int fd, c, res;
	struct termios oldtio, newtio;
	char buf[255];
	fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY);
	if ( fd < 0 ){
		perror(MODEMDEVICE);
		exit(-1);
	}
	newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;

	newtio.c_lflag = ICANON;
	tcflush(fd,TCIFLUSH);
	tcsetattr(fd,TCSANOW,&newtio);

	while (TRUE){
		res = read(fd,buf,255);
		buf[res] = 0;
		printf("%s",buf,res);
	}
	tcsetattr(fd,TCSANOW,&oldtio);
	close(fd);
}
