/*
 * Aplication.c
 *
 *  Created on: Aug 28, 2014
 *      Author: Germán
 */

#include "Comunicacion.h"
#include "RingBuffer.h"
#include "ComGalileo.h"
#include <string.h>

static UART_Desc deviceData;

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
}


static void SendChar(char ch, UART_Desc *desc)
{
	desc->isSent = FALSE;  /* this will be set to 1 once the block has been sent */
	while(ComGalileo_SendBlock(desc->handle, (LDD_TData*)&ch, 1)!=ERR_OK) {} /* Send char */
	while(!desc->isSent) {} /* wait until we get the green flag from the TX interrupt */
}

static void SendString(char *str,  UART_Desc *desc)
{
	while((*str)!='\0')
	{
		SendChar(*str, desc);
		str++;
	}
}

void mandarCadena(char* str)
{
	SendString(str, &deviceData);
}


