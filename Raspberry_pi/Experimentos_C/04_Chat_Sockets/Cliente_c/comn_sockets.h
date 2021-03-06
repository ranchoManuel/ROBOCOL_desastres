#ifndef COMN_SOCKETS_H
#define COMN_SOCKETS_H

#define BUFFSIZE 110
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

void init(char *server_address, unsigned short server_port);

void enviarCadena(char *texto);

void cerrarSocket();

#endif