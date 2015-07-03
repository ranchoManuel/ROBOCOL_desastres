/*
 * Utiles.c
 *
 *  Created on: Feb 13, 2015
 *      Author: Juan Manuel
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Comunicacion.h"

char **palabras;

void initEspacioMemoria(void)
{
	//Se quiere hacer solo un llamado a esta instruccion porque reserva memoria usando malloc.
	//Segun lo consultado cada llamado a un malloc reserva un pedazo diferente de memoria. En caso
	// contrario se nos podia ir toda
	palabras=(char**)malloc(10*sizeof(char**)); 
}

char ** split(char* instruccion ,char * cadena)
{
	char *aux;
	int tam, i;
	aux=strtok(instruccion, cadena);

	for(i=0; aux; i++)
	{
		palabras[i]=0;
		tam=strlen(aux);
		palabras[i]=(char*)malloc(tam);      
		memcpy(palabras[i], aux, tam);
		palabras[i][tam]=0;

		aux=strtok(0, cadena);
	}
	return (char**)palabras;
}

int parseInt(char* enString)
{
	int i;
	sscanf(enString, "%d", &i);
	return i;
}

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
	float lol = (x - in_min) * (out_max - out_min);
	lol = lol / (in_max - in_min);
	lol = lol + out_min;
	return lol;
}
