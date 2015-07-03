#include "uart_robocol.h"
#define BAUDRATE B115200

int main(int argc, char const *argv[]){
	char buf_tx[255];
	char buf_rx[255];
	struct termios newtio;
	newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD ;
	newtio.c_iflag = ICRNL;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
	newtio.c_cc[VMIN]=1;
	newtio.c_cc[VTIME]=0;
	uart_open(MODEMDEVICE,&newtio);
	while (1) {
		if (getWaitFlag()==FALSE ) {
			uart_read(&buf_rx,255);
			printf("%s",buf_rx);
		}
		setWaitFlag(TRUE);
		fgets(buf_tx, 255, stdin);
		uart_write(&buf_tx, 2);
		usleep(1000);
	}
	uart_close();
}

