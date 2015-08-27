#include "uart.h"

int main(){
	uart_init();
	while(1){
		printf("Presione:\n");
		while(getchar()!='\n');
		printf("%d",uart_write("TLT;"));
		usleep(1000);
		//getchar();
	}
}
