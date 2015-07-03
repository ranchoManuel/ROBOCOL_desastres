/*
 * Actuadores.h
 *
 *  Created on: Feb 07, 2015
 *      Author: Juan Manuel
 */

#ifndef MOVERBRAZOS_H_
#define MOVERBRAZOS_H_
 
#include "PE_Types.h"
#include "PE_LDD.h"
 
void enderezarBot(void);

void moverBrazos(int brazo1, int brazo2);

void setPWMsBrazos(int b1For, int b1Back, int b2For, int b2Back);

void moverOrugas(int oruga1, int oruga2);

void setPWMsOrugas(int o1Frontal, int o1Detras, int o2Frontal, int o2Detras);

void toogleIluminacion(void);

void toggleBuzzer(void);

#endif /* MOVERBRAZOS_H_ */
