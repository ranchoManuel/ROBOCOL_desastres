#include "comn_sockets1.h"
#include <stdio.h>		//printf, puts
#include <string.h>		//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>		//write
#include <stdlib.h>
#include "main.h"

char buffRead [BUFFSIZE];

//Este es para el thread de lectrua
pthread_t tid;

//Estos son para el socket
int socket_desc ,socket_fd ,c ,read_size, continuar;
struct sockaddr_in server , client;

//METODO QUE METO EN EL THREAD
void* leerEntrada()
{
	while(continuar)
	{
		//accept connection from an incoming client
    socket_fd = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if(socket_fd > 0)
    {
			puts("Connection socket accepted");
      //Receive a message from client
      while(1)
      {
				read_size=recv(socket_fd ,buffRead ,sizeof(buffRead) ,0);
        //Enviar el mensaje al otro pc
        enviarMensajeComp2(buffRead);

        memset(buffRead, 0, sizeof(buffRead));
        if(read_size == 0)
        {
					puts("Client socket disconnected");
          fflush(stdout);
          break;
        }
        else if(read_size == -1) perror("recv socket failed");
      }
    }
    else puts("Connection socket failed");
	}
	puts("Paro el Thread de comunicacion");
	pthread_exit(NULL);
}

void init_socket(unsigned short puerto)
{
	//Estos son para el Thread de lectura
	int err;
	char errMsj[50];//posible mensaje de error

	//Create socket
  socket_desc = socket(AF_INET , SOCK_STREAM , 0);
  if(socket_desc == -1) closeWithError("Could not create socket");
  puts("Server Socket created");

  //Prepare the sockaddr_in structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(puerto);

  //Bind
  if(bind(socket_desc, (struct sockaddr *)&server , sizeof(server)) < 0) closeWithError("bind failed(socket). Error");
  puts("bind done(socket)");

  //Listen
  listen(socket_desc , 3);

  //Accept and incoming connection
  c = sizeof(struct sockaddr_in);
  puts("Waiting for incoming connections(socket)...");

	continuar=true;
  //Aqui se crea el thread de lectura
  err = pthread_create(&(tid), NULL, &leerEntrada_1, NULL);
  if(err != 0)
	{
		sprintf(errMsj,"Can't create thread socket:[%s]", strerror(err));
    closeWithError(errMsj);
  }
  else printf("Thread socket created successfully\n");
}

void enviarCadena(char* texto)
{write(socket_fd ,texto ,strlen(texto));}

void cerrarSocket()
{
	continuar=false;
	usleep(100);
	close(socket_fd);
}
