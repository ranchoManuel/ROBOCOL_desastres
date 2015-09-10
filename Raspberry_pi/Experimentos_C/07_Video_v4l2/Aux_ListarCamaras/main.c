#include <stdio.h>

const int cantPuertos=1;
int myargc, camaraSeleccionada;
char **myargv;

void siguiente_camara()
{
	if(camaraSeleccionada+1 < myargc) camaraSeleccionada++;
	else camaraSeleccionada = 1+cantPuertos;
}    

void anterior_camara()
{
	if(camaraSeleccionada-1 > cantPuertos) camaraSeleccionada--;
	else camaraSeleccionada = myargc-1;
}   

void ver_seleccionada()
{puts(myargv[camaraSeleccionada]);}

int main(int argc, char **argv)
{
    myargc = argc;
    myargv = argv;
    camaraSeleccionada=1+cantPuertos;
    ver_seleccionada();

    siguiente_camara();
    ver_seleccionada();
    
    anterior_camara();
    ver_seleccionada();

    return 0;
}  
