#include "comn_sockets.h"
#include <sys/types.h>
#include <sys/socket.h> //socket
#include <stdio.h> //printf, perror
#include <netinet/in.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <stdlib.h> //exit
#include <string.h> //strlen
#include "main.h"

#define BUFFSIZE 110

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

char buffRead[BUFFSIZE];

//Este es para el thread de lectrua
pthread_t tid;

//Estos son para el socket
int client_socktfd;
struct sockaddr_in client_address;
int client_length;

//METODO QUE METO EN EL THREAD
void* leerEntrada()
{
	while(1)
	{
		memset(buffRead, 0, sizeof(buffRead));
		read(client_socktfd, &buffRead, BUFFSIZE);
		imprimirEnConsola(buffRead);
		fflush (stdout);
	}
}

void closeWithError(char *error)
{
	char errMsj[50];
	sprintf(errMsj, KRED"%s"RESET, error);
	perror(errMsj);
	exit(1);
}

void init(char *server_address, unsigned short server_port)
{
	//Estos son para el Thread de lectura
	int err;
	char errMsj[50];//posible mensaje de error

	//Aqui se establece la conexion con el socket
	if((client_socktfd=socket(AF_INET,SOCK_STREAM,0))<0)
			closeWithError("socket() fallo");

	memset(&client_address,0,sizeof(client_address));
	client_address.sin_family=AF_INET;
	client_address.sin_addr.s_addr=inet_addr(server_address);
	client_address.sin_port=htons(server_port);
	client_length=sizeof(client_address);
	puts("Triying Connection...");

	if(connect(client_socktfd, (struct sockaddr *)&client_address, client_length)==-1)
		closeWithError("Connection failed");

	puts(KGRN"Successful Connection"RESET);

	//Aqui se crea el thread de lectura
    err = pthread_create(&(tid), NULL, &leerEntrada, NULL);
    if(err != 0)
	{
        sprintf(errMsj,"Can't create thread:[%s]", strerror(err));
        closeWithError(errMsj);
    }
    else printf("Thread created successfully\n");
    printf(KCYN"___________________________\n"RESET);
}

void enviarCadena(char *texto)
{
	write(client_socktfd, texto, strlen(texto));
}

void cerrarSocket()
{
	close(client_socktfd);
}
