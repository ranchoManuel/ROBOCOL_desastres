#include "main.h"
#include "comn_sockets1.h"
#include "comn_sockets2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char buffWrite [BUFFSIZE];
	unsigned short port1, port2;

	if(argc!=3)
	{
		fprintf(stderr, "Uso: %s <Port1> <Port2>\n",argv[0]);
		exit(1);
	}
	port1=atoi(argv[1]);
	port2=atoi(argv[2]);

	init_1(port1);
	init_2(port2);

	while(1)
	{
		fflush(stdout);
		fgets(buffWrite, BUFFSIZE, stdin);
		//Es necesario quitarle el ultimo caracter porque es un enter '\n'
		buffWrite[strlen(buffWrite)-1] = '\0';
		if(strcmp("FIN", buffWrite)==0) break;
	}

	cerrarSocket_1();
	cerrarSocket_2();
	return 0;
}

void enviarMensajeComp1(char *texto)
{enviarCadena_1(texto);}

void enviarMensajeComp2(char *texto)
{enviarCadena_2(texto);}
