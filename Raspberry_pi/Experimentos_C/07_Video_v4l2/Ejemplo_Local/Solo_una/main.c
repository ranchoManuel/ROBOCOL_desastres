#include "main.h"
#include <linux/videodev2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "camara.h"
#include "pantalla.h"

#define BUFFSIZE 110

struct v4l2_format format;

int main(int argc, char* argv[])
{
	char buffWrite [BUFFSIZE];

	init_camara();
	init_pantalla(format);

	while(1)
	{
		fflush(stdout);
		fgets(buffWrite, BUFFSIZE, stdin);
		//Es necesario quitarle el ultimo caracter porque es un enter '\n'
		buffWrite[strlen(buffWrite)-1] = '\0';
		if(strcmp("FIN", buffWrite)==0) break;
	}

	close_camara();
	close_pantalla();

	return 0;
}

void establecer_format(struct v4l2_format formatP)
{format=formatP;}

void pintar_pantalla_paso1(void* mem, int size)
{pintar_pantalla_paso2(mem, size);}

void closeWithError(char *error)
{
	char errMsj[1024];
	sprintf(errMsj, KRED"%s"RESET, error);
	perror(errMsj);
	exit(1);
}
