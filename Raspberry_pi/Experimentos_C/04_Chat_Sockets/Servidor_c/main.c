#include "main.h"
#include "comn_sockets1.h"
#include "comn_sockets2.h" 
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
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
	while(1){}
	return 0;
}

void enviarMensajeComp1(char *texto)
{enviarCadena_1(texto);}

void enviarMensajeComp2(char *texto)
{enviarCadena_2(texto);}
