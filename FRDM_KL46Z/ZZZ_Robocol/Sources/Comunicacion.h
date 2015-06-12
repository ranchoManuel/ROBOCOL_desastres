/*
 * Comunicacion.h
 *
 *  Created on: Aug 28, 2014
 *      Author: Germán
 */

#ifndef COMUNICACION_H_
#define COMUNICACION_H_
 
#include "PE_Types.h"
#include "PE_LDD.h"
 
typedef struct {
  LDD_TDeviceData *handle; /* LDD device handle */
  volatile uint8_t isSent; /* this will be set to 1 once the block has been sent */
  uint8_t rxChar; /* single character buffer for receiving chars */
  uint8_t (*rxPutFct)(uint8_t); /* callback to put received character into buffer */
} UART_Desc;
 
void initComunicacion(void);

void mandarCadena(char* str);
 
#endif /* COMUNICACION_H_ */
