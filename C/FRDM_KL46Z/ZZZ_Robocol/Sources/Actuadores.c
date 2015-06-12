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

#define T 40
#define PWM_MAX 255

void enderezarBot(void) {

}

void moverBrazos(int brazo1, int brazo2) {
	int b1For = 0, b1Back = 0, b2For = 0, b2Back = 0;

	if (brazo1 < -255) {
		b1Back = 255;
	} else if (brazo1 > 255) {
		b1For = 255;
	}

	if (brazo2 < -255) {
		b2Back = 255;
	} else if (brazo2 > 255) {
		b2For = 255;
	}

	setPWMsBrazos(b1For, b1Back, b2For, b2Back);
}

void setPWMsBrazos(int b1For, int b1Back, int b2For, int b2Back) {
	int b1f = map(b1For, 0, PWM_MAX, T, 0);
	int b1b = map(b1Back, 0, PWM_MAX, T, 0);
	int b2f = map(b2For, 0, PWM_MAX, T, 0);
	int b2b = map(b2Back, 0, PWM_MAX, T, 0);

	BrazoFrontalForwardPWM_SetDutyUS(b1f);
	BrazoFrontalBackwardPWM_SetDutyUS(b1b);
	BrazoPostForwardPWM_SetDutyUS(b2f);
	BrazoPostBackwardPWM_SetDutyUS(b2b);
}

void moverOrugas(int oruga1, int oruga2) {
	int o1Frontal = 0;
	int o1Detras = 0;
	int o2Frontal = 0;
	int o2Detras = 0;

	if (oruga1 < -255) {
		o1Detras = 255;
	} else if (oruga1 > 255) {
		o1Frontal = 255;
	}

	if (oruga2 < -255) {
		o2Detras = 255;
	} else if (oruga2 > 255) {
		o2Frontal = 255;
	}

	setPWMsOrugas(o1Frontal, o1Detras, o2Frontal, o2Detras);
}

void setPWMsOrugas(int o1Frontal, int o1Detras, int o2Frontal, int o2Detras) {
	int o1adelante = map(o1Frontal, 0, PWM_MAX, T, 0);
	Oruga1BackwardPWM_SetDutyUS(o1adelante);
	int o1atras = map(o1Detras, 0, PWM_MAX, T, 0);
	Oruga2BackwardPWM_SetDutyUS(o1atras);
	int o2adelante = map(o2Frontal, 0, PWM_MAX, T, 0);
	Oruga2ForwardPWM_SetDutyUS(o2adelante);
	int o2atras = map(o2Detras, 0, PWM_MAX, T, 0);
	Oruga2BackwardPWM_SetDutyUS(o2atras);
}

void toogleIluminacion(void) {
	Luz_NegVal();
}

void toggleBuzzer(void) {
	Buzzer_NegVal();
}
