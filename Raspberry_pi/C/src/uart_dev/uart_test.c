#include "uart_robocol.h"
#define BAUDRATE B115200

int main(int argc, char const *argv[]){
	char buf_tx[255];
	char buf_rx[255];
	struct termios newtio;
	newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD ;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
	newtio.c_cc[VMIN]=1;
	newtio.c_cc[VTIME]=0;
	uart_open(MODEMDEVICE,&newtio);
	uint8_t i;
	while (1) {
	i=0;
	usleep(1000);
		if (getWaitFlag()==FALSE ) {
			uart_read(buf_rx,255);
			printf("%s\r\n", buf_rx);
		}
		setWaitFlag(TRUE);
		getchar();
	}
	uart_close();
}

