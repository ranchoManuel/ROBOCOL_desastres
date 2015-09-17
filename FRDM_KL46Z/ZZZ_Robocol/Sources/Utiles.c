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

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
	float lol = (x - in_min) * (out_max - out_min);
	lol = lol / (in_max - in_min);
	lol = lol + out_min;
	return lol;
}
