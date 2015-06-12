/* ###################################################################
 **     Filename    : main.c
 **     Project     : Practica 3
 **     Processor   : MKL46Z256VLL4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2015-01-31, 16:01, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */         
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */         
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Acelerometro.h"
#include "GI2C1.h"
#include "WAIT1.h"
#include "CI2C1.h"
#include "AdcTemp.h"
#include "AdcLdd1.h"
#include "RingBuffer.h"
#include "ComGalileo.h"
#include "TU2.h"
#include "Oruga1BackwardPWM.h"
#include "PwmLdd2.h"
#include "BrazoFrontalForwardPWM.h"
#include "PwmLdd3.h"
#include "TU3.h"
#include "Oruga1ForwardPWM.h"
#include "PwmLdd1.h"
#include "Oruga2BackwardPWM.h"
#include "PwmLdd4.h"
#include "TU1.h"
#include "BrazoPostForwardPWM.h"
#include "PwmLdd8.h"
#include "Oruga2ForwardPWM.h"
#include "PwmLdd5.h"
#include "BrazoFrontalBackwardPWM.h"
#include "PwmLdd6.h"
#include "BrazoPostBackwardPWM.h"
#include "PwmLdd7.h"
#include "BateriaInput.h"
#include "BitsIoLdd1.h"
#include "Luz.h"
#include "BitIoLdd1.h"
#include "Buzzer.h"
#include "BitIoLdd2.h"
#include "Rng1Gal.h"
#include "AS1.h"
#include "MAG1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Comunicacion.h"
#include "Actuadores.h"
#include "Utiles.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ADC 1
#define CAD 2
#define ZAR 3
#define END 4
#define TER 5
#define MCA 6
#define MBR 7
#define TGL 8
#define TGB 9

int param1, param2, zar=0, end=0, ter=0;

//TODO hacer mejor
int interpretarEtiqueta(char* instruccion)
{
	//mandarCadena("...Interpretando etiqueta\n");
	int rta=-1,i;
	char **palabras=split(instruccion,":");

	//Los primeros son cuando nos piden los sensores
	if(strcmp(palabras[0],"SEN;")==0) rta=ADC;
	else if(strcmp(palabras[0],"CAD;")==0) rta=CAD;
	//Estos nos piden empezar o finalizar un envio especial
	else if(strcmp(palabras[0],"ZAR;")==0) rta=ZAR;
	else if(strcmp(palabras[0],"END;")==0) rta=END;
	else if(strcmp(palabras[0],"TER;")==0) rta=TER;
	//Los demas activan actuadores
	else if(strcmp(palabras[0],"MCA")==0)
	{
		rta=MCA;
		param1=parseInt(palabras[1]);
		param2=parseInt(palabras[2]);
	}
	else if(strcmp(palabras[0],"MBR")==0)
	{
		rta=MBR;
		param1=parseInt(palabras[1]);
		param2=parseInt(palabras[2]);
	}
	else if(strcmp(palabras[0],"TGL;")==0) rta=TGL;
	else if(strcmp(palabras[0],"TGB;")==0) rta=TGB;
	else rta=0;
	//Liberando memoria - No funciona XD
	/*i = 0;
	while(palabras[i]) {
	    free(palabras[i]);
	    i++;
	}
	free(palabras);
	palabras = NULL;
	*/
	return rta;
	
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */
	// ch, i son auxiliares de lectura
	char temperatura=0, humedad=0, distancia=0, buffer[50], instruccion[32];
	unsigned char ch;
	int xAccel, yAccel, zAccel, i, etiqueta;
	int16_t magX, magY, magZ;

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	//1) Init Drivers
	initComunicacion();
	initEspacioMemoria();
	mandarCadena("---------ON---------\r\n");
	Acelerometro_Enable();
	Acelerometro_CalibrateX1g();
	Acelerometro_CalibrateY1g();
	Acelerometro_CalibrateZ1g();
	//TODO: Comentar(Debug)
	mandarCadena("1) Drivers iniciados\r\n");

	MAG1_Init();
	//MAG1_Enable();
	
	
	/* Write your code here */
	/* For example: for(;;) { } */
	for(;;)
	{
		//Cosas de procesar instrucciones
		if(RingBuffer_NofElements()!=0)//Hay cosas por leer
		{

			for(i=0; RingBuffer_NofElements()!=0 && i<32; i++)
			{
				(void)RingBuffer_Get(&ch); 
				instruccion[i]=ch;
				WAIT1_Waitms(1); 
			}
			instruccion[i]='\0'; 

			//2) Leer mensaje
			//mandarCadena("2) Mensaje: ");
			//mandarCadena(instruccion);
			//mandarCadena("\n");

			//3) Interpretar Mensaje
			//mandarCadena("3) Interpretar Etiqueta\n");
			etiqueta=interpretarEtiqueta(instruccion);
			//sprintf(buffer, "Etiqueta es: %d\n",etiqueta);
			//mandarCadena(buffer);

			switch(etiqueta)
			{
			case ADC: //Pide datos de humedad, temperatura, y distancia
				//5.1) Leer sensores
				//ADC 
				AdcTemp_MeasureChan(TRUE, 0);
				AdcTemp_GetChanValue(0, &temperatura);

				//5.2) Construir Respuesta ... 5.3) Enviar
				//Rta esperada "SEN:hum:tem:dis;"
				sprintf(buffer, "SEN:%5d:%5d:%5d;\r\n", humedad, temperatura, distancia);
				mandarCadena(buffer);

				break;
			case CAD: //Pide datos para pintar CAD (Acelerómetro)
				//5.1) Leer sensores
				//CAD 
				xAccel=Acelerometro_GetXmg();
				yAccel=Acelerometro_GetYmg();
				zAccel=Acelerometro_GetZmg();
				MAG1_GetX(&magX);
				MAG1_GetY(&magY);
				MAG1_GetZ(&magZ);

				//5.2) Construir Respuesta ... 5.3) Enviar
				//Rta esperada "CAD:acx:acy:acz:mAx:mAy:mAz;"
				sprintf(buffer, "CAD:%5d:%5d:%5d:%5d:%5d:%5d;\r\n",xAccel, yAccel, zAccel,
						magX ,magY ,magZ);
				mandarCadena(buffer);

				break;
			case ZAR: //Inicio de envío continuo de acelerómetro
				zar=1;

				break;
			case END: //Termina envío continuo de acelerómetro enviando la ultima info
				end=1;

				break;
			case TER: //Termina envío continuo de acelerómetro cortando de una
				ter=1;
				mandarCadena("OK;\r\n");

				break;
			case MCA: //Cambia valor de los PWM de las orugas [Derecha, Izquierda], por los valores dados por parámetro
				//5.2) Cambiar estado Orugas
				moverOrugas(param1, param2);
				mandarCadena("OK;\r\n");

				break;
			case MBR: //Cambia valor de los PWM de los brazos [Front, Back], por los valores dados por parámetro
				//5.2) Cambiar estado Brazos
				moverBrazos(param1, param2);
				mandarCadena("OK;\r\n");

				break;
			case TGL: //Enciende/apaga luces
				//5.2) Cambiar estado Actuadores
				toogleIluminacion();
				mandarCadena("OK;\r\n");

				break;
			case TGB: //Enciende/apaga buzzer
				//5.2) Cambiar estado Actuadores
				toggleBuzzer();
				mandarCadena("OK;\r\n");

				break;
			default:
				mandarCadena("ERR;\r\n");
				break;
			}
		}
		//Cosas del envio continuo
		if(ter==1) zar=end=ter=0;
		if(zar==1)
		{
			//5.1) Leer sensores
			//Acelerometro 
			xAccel=Acelerometro_GetXmg();
			yAccel=Acelerometro_GetYmg();
			zAccel=Acelerometro_GetZmg();

			//5.2) Construir Respuesta ... 5.3) Enviar
			//Rta esperada "ACE:acx:acy:acz;"
			sprintf(buffer, "ACE:%5d:%5d:%5d;\r\n", xAccel, yAccel, zAccel);
			mandarCadena(buffer);

		}
		if(end==1) zar=end=ter=0; 
	}

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.3 [05.09]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
