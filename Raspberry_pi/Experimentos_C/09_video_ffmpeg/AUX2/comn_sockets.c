#include "comn_sockets.h"
#include <stdio.h>		//printf, puts
#include <string.h>		//strlen
#include <unistd.h>		//write
#include <stdlib.h>
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include "main.h"

char buffReadSocket [BUFFSIZE];

//Este es para el thread de lectrua
pthread_t tid;

//Estos son para el socket
int socket_desc ,socket_fd ,c ,read_size, crearConeccion;
struct sockaddr_in server , client;

//METODO QUE METO EN EL THREAD
void* leerEntradaSocket(void *arg)
{
	while(1)
	{
		//accept connection from an incoming client
    socket_fd = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if(socket_fd > 0)
    {
			puts("Connection 1 accepted");
      //Receive a message from client
      while(1)
      {
				read_size=recv(socket_fd ,buffReadSocket ,sizeof(buffReadSocket) ,0);
        //Leer la instruccion que llega y decidir que camara mostrar

				if(strcmp("W", buffReadSocket)==0) camaraSiguiente();
				else if(strcmp("Q", buffReadSocket)==0) camaraAnterior();

        memset(buffReadSocket, 0, sizeof(buffReadSocket));
        if(read_size == 0)
        {
					puts("Client 1 disconnected");
          fflush(stdout);
          break;
        }
        else if(read_size == -1) perror("recv 1 failed");
      }
    }
    else puts("Connection 1 failed");
	}
}

void closeWithErrorSocket(char *error)
{
	char errMsj[50];
  sprintf(errMsj, KRED"%s"RESET, error);
  perror(errMsj);
  exit(1);
}

void initSocket(unsigned short puerto)
{
	//Estos son para el Thread de lectura
	int err;
	char errMsj[50];//posible mensaje de error

	//Create socket
  socket_desc = socket(AF_INET , SOCK_STREAM , 0);
  if(socket_desc == -1) closeWithErrorSocket("Could not create socket(1)");
  puts("Socket created(1)");

  //Prepare the sockaddr_in structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(puerto);

  //Bind
  if(bind(socket_desc, (struct sockaddr *)&server , sizeof(server)) < 0) closeWithErrorSocket("bind failed(1). Error");
  puts("bind done(1)");

  //Listen
  listen(socket_desc , 3);

  //Accept and incoming connection
  c = sizeof(struct sockaddr_in);
  puts("Waiting for incoming connections(1)...");

  //Aqui se crea el thread de lectura
  err = pthread_create(&(tid), NULL, &leerEntradaSocket, NULL);
  if(err != 0)
	{
		sprintf(errMsj,"Can't create thread 1:[%s]", strerror(err));
    closeWithErrorSocket(errMsj);
  }
  else printf("Thread 1 created successfully\n");
}

void enviarCadenaSocket(char* texto)
{write(socket_fd ,texto ,strlen(texto));}

void cerrarSocket()
{close(socket_fd);}
