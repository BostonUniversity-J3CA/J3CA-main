all: everything

everything: monitor.c serial_write.c
	gcc -Wall -g -o monitor.out monitor.c -ludev
	gcc -Wall -g -o serial_write.o serial_write.c -ludev

monitor: monitor.c
	gcc -Wall -g -o monitor.out monitor.c -ludev

write: serial_write.c
	gcc -Wall -g -o serial_write.o serial_write.c -ludev