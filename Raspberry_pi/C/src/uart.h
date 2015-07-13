#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <string.h>

#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyAMA0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE; 

void signal_handler_IO (int status);   /* definition of signal handler */
void uart_init();
void uart_close();

int fd,c, res;
struct termios oldtio,newtio;
struct sigaction saio;           /* definition of signal action */
char buf[255];
char buf_tx[255];
