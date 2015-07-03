/*
 * Actuadores.c
 *
 *  Created on: Feb 07, 2015
 *      Author: Juan Manuel
 */

#include "Actuadores.h"
#include "Oruga1BackwardPWM.h"
#include "Oruga1ForwardPWM.h"
#include "Oruga2BackwardPWM.h"
#include "Oruga2ForwardPWM.h"
#include "BrazoFrontalBackwardPWM.h"
#include "BrazoPostBackwardPWM.h"
#include "BrazoFrontalForwardPWM.h"
#include "BrazoPostForwardPWM.h"
#include "Luz.h"
#include "Buzzer.h"
#include "Utiles.h"
#include "Comunicacion.h"
#include <stdio.h>

#define T 40.0
#define PWM_MAX 255.0

void enderezarBot(void)
{
}

void moverBrazos(int brazo1, int brazo2)
{
	int b1For = 0, b1Back = 0, b2For = 0, b2Back = 0;

	if(brazo1 < 0)
	{
		b1Back = -brazo1;
		if(brazo1 > 255) b1Back = 255;
	}
	else if(brazo1 > 0)
	{
		b1For = brazo1;
		if(brazo1 > 255) b1For = 255;
	}

	if(brazo2 < 0)
	{
		b2Back = -brazo2;
		if(brazo2 > 255) b2Back = 255;
	}
	else if(brazo2 > 0)
	{
		b2For = brazo2;
		if (brazo2 > 255) b2For = 255;
	}

	setPWMsBrazos(b1For, b1Back, b2For, b2Back);
}

void setPWMsBrazos(int b1For, int b1Back, int b2For, int b2Back)
{
	float b1f = map((float)b1For, 0.0, PWM_MAX, T, 0.0);
	BrazoFrontalForwardPWM_SetDutyUS((int)b1f);
	
	float b1b = map((float)b1Back, 0.0, PWM_MAX, T, 0.0);
	BrazoFrontalBackwardPWM_SetDutyUS((int)b1b);
	
	float b2f = map((float)b2For, 0.0, PWM_MAX, T, 0.0);
	BrazoPostForwardPWM_SetDutyUS((int)b2f);
	
	float b2b = map((float)b2Back, 0.0, PWM_MAX, T, 0.0);
	BrazoPostBackwardPWM_SetDutyUS((int)b2b);
}

void moverOrugas(int oruga1, int oruga2)
{
	int o1Frontal=0, o1Detras=0, o2Frontal=0, o2Detras=0;

	if(oruga1 < 0)
	{
		o1Detras = -oruga1;
		if(oruga1 > 255) o1Detras = 255; 
	}
	else if(oruga1 > 0)
	{
		o1Frontal = oruga1;
		if(oruga1 > 255) o1Frontal = 255;
	}
	
	if(oruga2 < 0)
	{
		o2Detras = -oruga2;
		if (oruga2 > 255) o2Detras = 255;
	}
	else if(oruga2 > 0)
	{
		o2Frontal = oruga2;
		if(oruga2 > 255) o2Frontal = 255;
	}
	setPWMsOrugas(o1Frontal, o1Detras, o2Frontal, o2Detras);
}

void setPWMsOrugas(int o1Frontal, int o1Detras, int o2Frontal, int o2Detras)
{
	float o1adelante = map((float)o1Frontal, 0.0, PWM_MAX, T, 0.0);
	Oruga1ForwardPWM_SetDutyUS((int)o1adelante);
	
	float o1atras = map((float)o1Detras, 0.0, PWM_MAX, T, 0.0);
	Oruga1BackwardPWM_SetDutyUS((int)o1atras);
	
	float o2adelante = map((float)o2Frontal, 0.0, PWM_MAX, T, 0.0);
	Oruga2ForwardPWM_SetDutyUS((int)o2adelante);
	
	float o2atras = map((float)o2Detras, 0.0, PWM_MAX, T, 0.0);
	Oruga2BackwardPWM_SetDutyUS((int)o2atras);
}

void toogleIluminacion(void)
{
	Luz_NegVal();
}

void toggleBuzzer(void)
{
	Buzzer_NegVal();
}
