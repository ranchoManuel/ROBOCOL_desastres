#include "comn_sockets1.h"
#include <stdio.h>		//printf, puts
#include <string.h>		//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>		//write
#include <stdlib.h>
#include "main.h"

#define BUFFSIZE 110

#define true	1
#define false	0
#define KRED  "\x1B[31m"
#define RESET "\033[0m"

char buffRead [BUFFSIZE];

//Este es para el thread de lectrua
pthread_t tid;

//Estos son para el socket
int socket_desc ,client_sock ,c ,read_size, crearConeccion;
struct sockaddr_in server , client;

//METODO QUE METO EN EL THREAD
void* leerEntrada_1()
{
	while(1)
    {
        //accept connection from an incoming client
        client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
        if(client_sock > 0)
        {
            puts("Connection 1 accepted");
            //Receive a message from client
            while(1)
            {
                read_size=recv(client_sock ,buffRead ,sizeof(buffRead) ,0);
                //Enviar el mensaje al otro pc
                enviarMensajeComp2(buffRead);
                
                memset(buffRead, 0, sizeof(buffRead));
                if(read_size == 0)
                {
                    puts("Client 1 disconnected");
                    fflush(stdout);
                    crearConeccion=true;
                    break;
                }
                else if(read_size == -1) perror("recv 1 failed");
            }
        }
        else puts("Connection 1 failed");
     }
}

void closeWithError_1(char *error)
{
    char errMsj[50];
    sprintf(errMsj, KRED"%s"RESET, error);
    perror(errMsj);
    exit(1);
}

void init_1(unsigned short puerto)
{
	//Estos son para el Thread de lectura
	int err;
	char errMsj[50];//posible mensaje de error

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if(socket_desc == -1)
        closeWithError_1("Could not create socket(1)");
    
    puts("Socket created(1)");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(puerto);
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
        closeWithError_1("bind failed(1). Error");
        
    puts("bind done(1)");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    int crearConeccion=true;
    c = sizeof(struct sockaddr_in);
    puts("Waiting for incoming connections(1)...");
    
    //Aqui se crea el thread de lectura
    err = pthread_create(&(tid), NULL, &leerEntrada_1, NULL);
    if(err != 0)
	{
        sprintf(errMsj,"Can't create thread 1:[%s]", strerror(err));
        closeWithError_1(errMsj);
    }
    else printf("Thread 1 created successfully\n");
}

void enviarCadena_1(char* texto)
{
	write(client_sock ,texto ,strlen(texto));
}
