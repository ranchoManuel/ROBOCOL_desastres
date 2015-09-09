#ifndef COMN_SERIAL_H
#define COMN_SERIAL_H

void initSerial(char *serialport, int baud);

void enviarCadenaSerial(char *texto);

void cerrarSerial();

#endif
