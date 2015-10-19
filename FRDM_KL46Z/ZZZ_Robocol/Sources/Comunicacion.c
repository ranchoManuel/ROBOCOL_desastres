/*
 * Aplication.c
 *
 *  Created on: Aug 28, 2014
 *      Author: Germán
 */

#include "Comunicacion.h"
#include "RingBuffer.h"
#include "Rng1Gal.h"
#include "AS1.h"
#include "ComGalileo.h"
#include <string.h>

static UART_Desc deviceData;
static UART_Desc sensorData;

void initComunicacion(void)
{
	/* initialize struct fields */
	deviceData.handle = ComGalileo_Init(&deviceData);
	deviceData.isSent = FALSE;
	deviceData.rxChar = '\0';
	deviceData.rxPutFct = RingBuffer_Put;
	/* set up to receive RX into input buffer */
	RingBuffer_Init(); /* initialize RX buffer */
	/* Set up ReceiveBlock() with a single byte buffer. We will be called in OnBlockReceived() event. */
	while(ComGalileo_ReceiveBlock(deviceData.handle, (LDD_TData *)&deviceData.rxChar, sizeof(deviceData.rxChar))!=ERR_OK) {} /* initial kick off for receiving data */

	/* initialize struct fields */
	sensorData.handle = AS1_Init(&sensorData);
	sensorData.isSent = FALSE;
	sensorData.rxChar = '\0';
	sensorData.rxPutFct = Rng1Gal_Put;
	/* set up to receive RX into input buffer */
	Rng1Gal_Init(); /* initialize RX buffer */
	/* Set up ReceiveBlock() with a single byte buffer. We will be called in OnBlockReceived() event. */
	while(AS1_ReceiveBlock(sensorData.handle, (LDD_TData *)&sensorData.rxChar, sizeof(sensorData.rxChar))!=ERR_OK) {} /* initial kick off for receiving data */
}


static void SendChar(char ch, UART_Desc *desc)
{
	desc->isSent = FALSE;  /* this will be set to 1 once the block has been sent */
	while(ComGalileo_SendBlock(desc->handle, (LDD_TData*)&ch, 1)!=ERR_OK) {} /* Send char */
	while(!desc->isSent) {} /* wait until we get the green flag from the TX interrupt */
}

//Para el sensor
static void SendChar2(char ch, UART_Desc *desc)
{
	desc->isSent = FALSE;  /* this will be set to 1 once the block has been sent */
	while(AS1_SendBlock(desc->handle, (LDD_TData*)&ch, 1)!=ERR_OK) {} /* Send char */
	while(!desc->isSent) {} /* wait until we get the green flag from the TX interrupt */
}

static void SendString(char *str,  UART_Desc *desc, int aQuien)
{
	while((*str)!='\0')
	{
		if(aQuien==0) SendChar(*str, desc);
		else SendChar2(*str, desc);
		str++;
	}
}

void mandarCadena(char* str, int aQuien)
{
	if(aQuien==0) SendString(str, &deviceData, aQuien);
	else SendString(str, &sensorData, aQuien);
}


