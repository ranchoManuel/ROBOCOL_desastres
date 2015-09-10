#include "main.h"
#include "comn_sockets.h"
#include "pantalla.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buffWrite[BUFFSIZE];
char key[]="FIN";

int main(int argc, char *argv[])
{
	unsigned short server_port;
	char *server_address;

	if(argc!=3)
	{
		fprintf(stderr, "Uso: %s <Server IP> <Echo Port>\n",argv[0]);
		exit(1);
	}
	server_address=argv[1];
	server_port=atoi(argv[2]);
	
	init(server_address, server_port);
	init_pantalla();

	while(1)
	{
		fflush(stdout);
		fgets(buffWrite, BUFFSIZE, stdin);
		//Es necesario quitarle el ultimo caracter porque es un enter '\n'
		buffWrite[strlen(buffWrite)-1] = '\0';
		if(strcmp(key, buffWrite)==0) break;
		
		enviarCadena(buffWrite);
	}

	cerrarSocket();
	close_pantalla();
	return 0;
}

void pintar_pantalla_paso1(void* buffer, int tamBuffer)
{pintar_pantalla_paso2(buffer, tamBuffer);}

