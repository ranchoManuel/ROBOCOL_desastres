#ifndef MAIN_H
#define MAIN_H

#define true 	1
#define false 	0

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

void pintar_pantalla_paso1(void* mem, int size);

void closeWithError(char *error);

#endif
