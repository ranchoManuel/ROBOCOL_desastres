#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include "main.h"
#include "comn_sockets.h"

// ------------------------CONSTANTES------------------------
const char* parte1="ffmpeg -loglevel quiet -i";
//parte 2 es una camara ejemplo: /dev/video0
const char* parte3="-s 640x480 -pix_fmt yuv420p -r 60 -fflags nobuffer -an -f mpegts udp://";
const char* ip ="127.0.0.1";
const char* parte5=":10000 &";

// ------------------------ATRIBUTOS------------------------
char buffWrite [BUFFSIZE];
char comando[BUFFSIZE];
char** camaras;
int numCamaras, esta;

// ------------------------METODOS------------------------
int main(int argc, char** argv)
{
	//1) Agarrar los parametros del programa
	esta=2;
	if(argc<=2)
	{
		fprintf(stderr, "Uso: %s <... list of cameras ...>\n",argv[0]);
		exit(1);
	}
	int socketPort=atoi(argv[1]);

	camaras = malloc(argc * PADDING * sizeof(char));

	int i = 0;
	for(; i < argc; i++)
	{
    	*(camaras + i) = malloc(sizeof(char) * (strlen(*(argv + i))));
    	strcpy(*(camaras + i), *(argv + i));
			printf("%s\n", *(camaras + i));
	}

	//2) Inicializar el thread del socket y la camara 1
	initSocket(socketPort);

	puts("Init de camara");
	sprintf(comando,"%s %s %s%s%s", parte1, *(camaras + esta), parte3, ip, parte5);
	printf("Comando: %s\n", comando);
	system(comando);

	//3) Atrapar todo en un ciclo
	while(1)
	{
		fflush(stdout);
		fgets(buffWrite, BUFFSIZE, stdin);
		//Es necesario quitarle el ultimo caracter porque es un enter '\n'
		buffWrite[strlen(buffWrite)-1] = '\0';
		if(strcmp("FIN", buffWrite)==0)
		{
			system("killall ffmpeg");
			cerrarSocket();
			break;
		}
		else if(strcmp("W", buffWrite)==0) camaraSiguiente();
		else if(strcmp("Q", buffWrite)==0) camaraAnterior();
	}

	cerrarSocket();
	return 0;
}

void camaraSiguiente()
{
	system("killall ffmpeg");
	printf("numero de camaras: %d\n", numCamaras);
	esta=(esta+1<(CANTCAMS+2))?esta+1:2;
	printf("Esta: %d, Sig: %s\n", esta, *(camaras + esta));
	sprintf(comando,"%s %s %s%s%s", parte1, *(camaras + esta), parte3, ip, parte5);
	puts(comando);
	system(comando);
	enviarCadenaSocket("OK;");
}

void camaraAnterior()
{
	system("killall ffmpeg");
	esta=(esta-1>=2)?esta-1:(CANTCAMS+2)-1;
	printf("Esta: %d, Ant: %s\n", esta, *(camaras + esta));
	sprintf(comando,"%s %s %s%s%s", parte1, *(camaras + esta), parte3, ip, parte5);
	puts(comando);
	system(comando);
	enviarCadenaSocket("OK;");
}
