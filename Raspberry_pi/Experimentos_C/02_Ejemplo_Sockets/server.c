#include <stdio.h>		//printf, puts
#include <string.h>		//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>		//write

#define PUERTO	1235
#define BUFF_SIZE 110

int main()
{
  int socket_desc , client_sock , c , read_size;
  struct sockaddr_in server , client;
  char buff[BUFF_SIZE];

  //Create socket
  socket_desc = socket(AF_INET , SOCK_STREAM , 0);
  if(socket_desc == -1)
  {
  	printf("Could not create socket");
  	return 1;
  }
  puts("Socket created");

  //Prepare the sockaddr_in structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(PUERTO);

  //Bind
  if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
  {
      //print the error message
      perror("bind failed. Error");
      return 1;
  }
  puts("bind done");

  //Listen
  listen(socket_desc , 3);

  //Accept and incoming connection
  puts("Waiting for incoming connections...");
  c = sizeof(struct sockaddr_in);
  while(1)
	{
    //accept connection from an incoming client
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if(client_sock > 0)
		{
			puts("Connection accepted");
			//Receive a message from client
			while(1)
			{
				read_size = recv(client_sock , buff , sizeof(buff) , 0);
				//Send the message back to client
				write(client_sock , buff , strlen(buff));
				memset(buff, 0, sizeof(buff));

				if(read_size == 0)
				{
					puts("Client disconnected");
					fflush(stdout);
					break;
				}
				else if(read_size == -1) perror("recv failed");
			}
		}
		else puts("Connection failed");
  }
  return 0;
}
