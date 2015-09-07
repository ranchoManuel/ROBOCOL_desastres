#include "comn_sockets2.h"
#include <stdio.h>		//printf, puts
#include <string.h>		//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>		//write
#include <stdlib.h>
#include "main.h"

#define BUFFSIZE 110

#define KRED  "\x1B[31m"
#define RESET "\033[0m"

char buffRead2 [BUFFSIZE];

//Este es para el thread de lectrua
pthread_t tid2;

//Estos son para el socket
int socket_desc2 ,client_sock2 ,c2 ,read_size2;
struct sockaddr_in server2 , client2;

//METODO QUE METO EN EL THREAD
void* leerEntrada_2()
{
	while(1)
    {
        //accept connection from an incoming client
        client_sock2 = accept(socket_desc2, (struct sockaddr *)&client2, (socklen_t*)&c2);
        if(client_sock2 > 0)
        {
            puts("Connection 2 accepted");
            //Receive a message from client
            while(1)
            {
                read_size2=recv(client_sock2 ,buffRead2 ,sizeof(buffRead2) ,0);
                //Enviar el mensaje al otro pc
                enviarMensajeComp1(buffRead2);
                
                memset(buffRead2, 0, sizeof(buffRead2));
                if(read_size2 == 0)
                {
                    puts("Client 2 disconnected");
                    fflush(stdout);
                    break;
                }
                else if(read_size2 == -1) perror("recv 2 failed");
            }
        }
        else puts("Connection 2 failed");
     }
}

void closeWithError_2(char *error2)
{
    char errMsj2[50];
    sprintf(errMsj2, KRED"%s"RESET, error2);
    perror(errMsj2);
    exit(1);
}

void init_2(unsigned short puerto2)
{
	//Estos son para el Thread de lectura
	int err2;
	char errMsj2[50];//posible mensaje de error

    //Create socket
    socket_desc2 = socket(AF_INET , SOCK_STREAM , 0);
    if(socket_desc2 == -1)
        closeWithError_2("Could not create socket(2)");
    
    puts("Socket created(2)");
     
    //Prepare the sockaddr_in structure
    server2.sin_family = AF_INET;
    server2.sin_addr.s_addr = INADDR_ANY;
    server2.sin_port = htons(puerto2);
     
    //Bind
    if( bind(socket_desc2,(struct sockaddr *)&server2 , sizeof(server2)) < 0)
        closeWithError_2("bind failed. Error(2)");
        
    puts("bind done(2)");
     
    //Listen
    listen(socket_desc2 , 3);
     
    //Accept and incoming connection
    c2 = sizeof(struct sockaddr_in);
    puts("Waiting for incoming connections(2)...");
    
    //Aqui se crea el thread de lectura
    err2 = pthread_create(&(tid2), NULL, &leerEntrada_2, NULL);
    if(err2 != 0)
	{
        sprintf(errMsj2,"Can't create thread 2:[%s]", strerror(err2));
        closeWithError_1(errMsj2);
    }
    else printf("Thread 2 created successfully\n");
}

void enviarCadena_2(char* texto2)
{
	write(client_sock2 ,texto2 ,strlen(texto2));
}
