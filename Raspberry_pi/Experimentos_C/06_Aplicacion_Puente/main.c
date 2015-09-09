#include "main.h"
#include "comn_sockets.h"
#include "comn_serial.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFSIZE 110

int main(int argc, char *argv[])
{
	char buffWrite [BUFFSIZE];
	unsigned short socketPort;
	char *serialport;
	int baud;

	if(argc!=4)
	{
		fprintf(stderr, "Uso: %s <Socket Port> <Serial Port> <baud>\n",argv[0]);
		exit(1);
	}
	socketPort=atoi(argv[1]);
	serialport=argv[2];
	baud=atoi(argv[3]);

	initSocket(socketPort);
	initSerial(serialport, baud);

	while(1)
	{
		fflush(stdout);
		fgets(buffWrite, BUFFSIZE, stdin);
		//Es necesario quitarle el ultimo caracter porque es un enter '\n'
		buffWrite[strlen(buffWrite)-1] = '\0';
		if(strcmp("FIN", buffWrite)==0) break;
	}

	cerrarSerial();
	cerrarSocket();
	return 0;
}

void enviarMensaje_a_Socket(char *texto)
{enviarCadenaSocket(texto);}

void enviarMensaje_a_Serial(char *texto)
{enviarCadenaSerial(texto);}
