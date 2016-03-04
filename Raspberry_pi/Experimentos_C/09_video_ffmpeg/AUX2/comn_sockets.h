#ifndef COMN_SOCKETS_H
#define COMN_SOCKETS_H

void initSocket(unsigned short puerto, char* ip, int argc, char** argv);

void enviarCadenaSocket(char* texto);

void cerrarSocket();

#endif
