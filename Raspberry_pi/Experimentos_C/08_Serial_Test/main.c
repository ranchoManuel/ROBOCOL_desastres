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
		else if(strcmp("M1", buffWrite)==0)	enviarCadenaSerial("MCA:300:0;");
		else if(strcmp("M2", buffWrite)==0)	enviarCadenaSerial("MCA:0:300;");
		else if(strcmp("B1", buffWrite)==0)	enviarCadenaSerial("MBR:300:0;");
		else if(strcmp("B2", buffWrite)==0)	enviarCadenaSerial("MBR:0:300;");
		else if(strcmp("S", buffWrite)==0)	enviarCadenaSerial("SEN;");
		else if(strcmp("C", buffWrite)==0)	enviarCadenaSerial("CAD;");
		else if(strcmp("L", buffWrite)==0)	enviarCadenaSerial("TGL;");
		else if(strcmp("P", buffWrite)==0)	enviarCadenaSerial("TGB;");
	}

	cerrarSerial();
	return 0;
}

void imprimirEnConsola(char *texto)
{printf(KBLU "Other: "RESET"%s\n", texto);}
