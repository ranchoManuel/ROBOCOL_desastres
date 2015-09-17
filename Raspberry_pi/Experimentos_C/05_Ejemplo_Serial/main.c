#include "main.h"
#include "comn_serial.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFSIZE 110

#define KBLU  "\x1B[34m"
#define RESET "\033[0m"

char buffWrite[BUFFSIZE];

int main(int argc, char *argv[])
{
	char *serialport;
	int baud;

	if(argc!=3)
	{
		fprintf(stderr, "Uso: %s <Serial Port> <baud>\n",argv[0]);
		exit(1);
	}
	serialport=argv[1];
	baud=atoi(argv[2]);
	
	initSerial(serialport, baud);

	while(1)
	{
		fflush(stdout);
		fgets(buffWrite, BUFFSIZE, stdin);
		//Es necesario quitarle el ultimo caracter porque es un enter '\n'
		buffWrite[strlen(buffWrite)-1] = '\0';
		if(strcmp("FIN", buffWrite)==0) break;
		
		enviarCadenaSerial(buffWrite);
	}

	cerrarSerial();
	return 0;
}

void imprimirEnConsola(char *texto)
{printf(KBLU "Other: "RESET"%s\n", texto);}
