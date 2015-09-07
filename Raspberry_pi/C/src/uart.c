#include "uart.h"

  /***************************************************************************
  * signal handler. This function save the message when the event is 		 *
  * generated
  ***************************************************************************/

  void signal_handler_IO (int status)
  {
	/* We sleep the program because we have to wait for a full buffer	*/
  	usleep(10000);
  	res = read(fd,buf_rx,255);
  	buf_rx[res]='\0';
  	printf("%s\n", buf_rx);
  }

  void uart_init()
  {
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

  void uart_close(){
	/* restore old port settings */
	tcsetattr(fd,TCSANOW,&oldtio);
  }

  void uart_write(char *buff){
  	int size=strlen(buff);
  	strcpy(buf_tx,buff);
  	buf_tx[size]='\0';
  	write(fd,buf_tx,size);
  }
