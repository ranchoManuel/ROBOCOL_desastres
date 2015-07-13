#include "uart.h"

int main()
{
	uart_init();
	/* loop while waiting for input. normally we would do something
	   useful here */
	while (STOP==FALSE) {
	 /* after receiving SIGIO, wait_flag = FALSE, input is available
	 and can be read */
	// printf("escriba");

	// printf("escribio");
	// if(strlen(buf_tx)>0){
	// }
	//if (res==1) STOP=TRUE; /* stop loop if only a CR was input */
	//wait_flag = TRUE;      /* wait for new input */
	}
	/* restore old port settings */
	tcsetattr(fd,TCSANOW,&oldtio);
}

  /***************************************************************************
  * signal handler. sets wait_flag to FALSE, to indicate above loop that     *
  * characters have been received.                                           *
  ***************************************************************************/

void signal_handler_IO (int status)
{
	//printf("received SIGIO signal.\n");
	usleep(10000);
	//wait_flag = FALSE;
	res = read(fd,buf,255);
	buf[res]=0;
	printf("%s\n", buf);
	//fgets(buf_tx, 100, stdin);
	//if(strlen(buf_tx)>0){
	//	buf_tx[strlen(buf_tx)-1]=0;
	//	write(fd, buf_tx, 100);
	//	buf_tx[0]=0;
	//}
	buf[0]='\0';
}

  void uart_init(){
	/* open the device to be non-blocking (read will return immediatly) */
	fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd <0) {perror(MODEMDEVICE); exit(-1); }

	/* install the signal handler before making the device asynchronous */
	saio.sa_handler = signal_handler_IO;
	sigemptyset(&saio.sa_mask);
	saio.sa_flags = 0;
	saio.sa_restorer = NULL;
	sigaction(SIGIO,&saio,NULL);

	/* allow the process to receive SIGIO */
	fcntl(fd, F_SETOWN, getpid());
	/* Make the file descriptor asynchronous (the manual page says only 
	   O_APPEND and O_NONBLOCK, will work with F_SETFL...) */
	fcntl(fd, F_SETFL, FASYNC);
	
	tcgetattr(fd,&oldtio); /* save current port settings */
	/* set new port settings for canonical input processing */
	newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
	newtio.c_cc[VMIN]=1;
	newtio.c_cc[VTIME]=0;
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&newtio);
}
