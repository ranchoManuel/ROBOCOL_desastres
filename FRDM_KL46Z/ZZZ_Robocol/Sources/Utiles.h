/*
 * Utiles.h
 *
 *  Created on: Feb 13, 2015
 *      Author: USER
 */

#ifndef UTILES_H_
#define UTILES_H_

char ** split(char* instruccion ,char * cadena);

int parseInt(char* enString);

float map(float x, float in_min, float in_max, float out_min, float out_max);

void initEspacioMemoria(void);

#endif /* UTILES_H_ */
