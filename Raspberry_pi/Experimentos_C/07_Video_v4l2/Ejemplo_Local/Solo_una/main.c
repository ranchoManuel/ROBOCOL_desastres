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
const int cantPuertos=1;
int myargc, camaraSeleccionada;
char **myargv;

void siguiente_camara()
{
	if(camaraSeleccionada+1 < myargc) camaraSeleccionada++;
	else camaraSeleccionada = 1+cantPuertos;
}

void anterior_camara()
{
	if(camaraSeleccionada-1 > cantPuertos) camaraSeleccionada--;
	else camaraSeleccionada = myargc-1;
}

int main(int argc, char* argv[])
{
	myargc = argc;
	myargv = argv;
  camaraSeleccionada=1+cantPuertos;

	char buffWrite [BUFFSIZE];

	init_camaras(cantPuertos, argc, argv);
	init_pantalla(format);

	while(1)
	{
		fflush(stdout);
		fgets(buffWrite, BUFFSIZE, stdin);
		//Es necesario quitarle el ultimo caracter porque es un enter '\n'
		buffWrite[strlen(buffWrite)-1] = '\0';
		if(strcmp("FIN", buffWrite)==0) break;
		/*else if(strcmp("M", buffWrite)==0)
		{
			close_camara();
			siguiente_camara();
			init_camaras(cantPuertos, argc, argv);
		}
		else if(strcmp("N", buffWrite)==0)
		{
			close_camara();
			anterior_camara();
			init_camaras(cantPuertos, argc, argv);
		}
		*/
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
