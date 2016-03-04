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
//parte 4 es la ip de donde queremos proyectar el video ejemplo 192.168.0.1
const char* parte5=":10000 &";

// ------------------------ATRIBUTOS------------------------
char buffWrite [BUFFSIZE];
char comando[BUFFSIZE];
char** camaras;
int numCamaras, esta;

// ------------------------PROTOTIPOS DE FUNCIONES------------------------
void camaraSiguiente(int argc, char** argv, char* ip);
void camaraAnterior(int argc, char** argv, char* ip);

// ------------------------METODOS------------------------
int main(int argc, char** argv)
{
	//1) Agarrar los parametros del programa
	esta=3;
	if(argc<=3)
	{
		fprintf(stderr, "Uso: %s <Socket Port> <ip> <... list of cameras ...>\n",argv[0]);
		exit(1);
	}
	int socketPort=atoi(argv[1]);
	char* ip=argv[2];

	//2) Inicializar el thread del socket y la camara 1
	initSocket(socketPort, ip, argc, argv);

	puts("Init de camara");
	sprintf(comando,"%s %s %s%s%s", parte1, argv[esta], parte3, ip, parte5);
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
			break;
		}
		else if(strcmp("W", buffWrite)==0) camaraSiguiente(argc, argv, ip);
		else if(strcmp("Q", buffWrite)==0) camaraAnterior(argc, argv, ip);
	}

	cerrarSocket();
	return 0;
}

void camaraSiguiente(int argc, char** argv, char* ip)
{
	system("killall ffmpeg");
	esta=(esta+1<argc)?esta+1:3; // (3), porque el primer argumento es el puerto del socket y el segundo es la ip
	printf("Sig: %s\n", argv[esta]);
	sprintf(comando,"%s %s %s%s%s", parte1, argv[esta], parte3, ip, parte5);
	puts(comando);
	system(comando);
	enviarCadenaSocket("OK;");
}

void camaraAnterior(int argc, char** argv, char* ip)
{
	system("killall ffmpeg");
	esta=(esta-1>=3)?esta-1:argc-1;// (>=3), porque el primer argumento es el puerto del socket y el segundo es la ip
	printf("Ant: %s\n", argv[esta]);
	sprintf(comando,"%s %s %s%s%s", parte1, argv[esta], parte3, ip, parte5);
	puts(comando);
	system(comando);
	enviarCadenaSocket("OK;");
}
