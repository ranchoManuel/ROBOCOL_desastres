#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "robocol_queue.h"
#include "robocol_list.h"
#include "command.h"
#include "uart.h"

#define NOT_A_COMMAND_RESPONSE "NAC"
#define MAX_RESPONSE_DEPTH 3
#define OK_RESPONSE "OK"

#define TOTAL_RESPONSE_SIZE 100

// gcc -o program driver.c robocol_queue.c robocol_list.c uart.c

float hum, ten, dis;
float acy, acx, acz;
float max, may, maz;

int split_line(char *buf, char **argv, int max_args) {
    int arg = 0;

    while (isspace(*buf)) buf++;

    for (; arg < max_args && *buf != '\0'; arg++) {
    	argv[arg] = buf;
      	while (*buf != '\0' && !isspace(*buf)) buf++;
      	if (*buf != '\0') {
        	*buf = '\0';
        	buf++;
      	}
      	while (isspace(*buf)) buf++;
    }
    return arg;
}

void reverse(char *str, int len) {
    int i = 0, j = len - 1, temp;
    while(i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

int int_string(int x, char* str, int d) {
    int i = 0;
    while(x != 0) {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    while (i < d)
        str[i++] = '0';
 
    reverse(str, i);
    str[i] = '\0';
    return i;
}

void float_string(float n, char *res, int afterpoint) {
    int ipart = (int) n;
    float fpart = n - (float) ipart;
 
    int i = int_string(ipart, res, 0);
 
    if (afterpoint != 0) {
        res[i] = '.';
        fpart = fpart * pow(10, afterpoint); 
        int_string((int)fpart, res + i + 1, afterpoint);
    }
}

char* format_string(char* id, float args[], int n, int* new_size) {
	int total_size = 0;
	total_size += 1 + strlen(id);

	char new_args[6][4];
	static char ans[TOTAL_RESPONSE_SIZE];
	strcat(ans, id);
	strcat(ans, (char*) ":");

	int i = 0;
	float item;
	char dummy[3 + MAX_RESPONSE_DEPTH];
	for(; i < n; i++) {
		item = args[i];
		float_string(item, dummy, MAX_RESPONSE_DEPTH);
		total_size += 1 + strlen(dummy);
		strcat(ans, dummy);
		if(i == n - 1)
			strcat(ans, (char*) ";");
		else
			strcat(ans, (char*) ":");
	}

	total_size += 1;
	*new_size = total_size;

	return ans;
}

char* get_command_response(char* name, int* size) {
	if(strcmp(name, "SEN") == 0) {
		float array[] = {hum, ten, dis};
		int array_size = sizeof(array) / sizeof(array[0]);
		return format_string(name, array, array_size, size);
	}

	else if(strcmp(name, "CAD") == 0) {
		float array[] = {acx, acy, acz, max, may, maz};
		int array_size = sizeof(array) / sizeof(array[0]);
		return format_string(name, array, array_size, size);
	}

	else if(strcmp(name, "MCA") == 0)
		return OK_RESPONSE;

	else if(strcmp(name, "MBR") == 0)
		return OK_RESPONSE;

	else if(strcmp(name, "TGL") == 0)
		return OK_RESPONSE;

	else if(strcmp(name, "TGB") == 0)
		return OK_RESPONSE;

	else if(strcmp(name, "ZAR") == 0 || strcmp(name, "END") == 0) {
		float array[] = {acx, acy, acz};
		int array_size = sizeof(array) / sizeof(array[0]);
		return format_string(name, array, array_size, size);
	}

	else if(strcmp(name, "TER") == 0)
		return OK_RESPONSE;

	return NOT_A_COMMAND_RESPONSE;
}

char* get_command_proposal(char* name) {
	static char ans[100];
	command* c;

	if(strcmp(name, "MCA") == 0) {
		c = init_command(name, "PWMD", "PWMI");
	} else if(strcmp(name, "MCA") == 0) {
		c = init_command(name, "PWMF", "PWMB");
	} else {
		c = init_command(name, "", "");
	}
	
	strcpy(ans, command_string(c));
	destroy_command(c);

	return ans;
}

int main(void) {
	uart_init();
    queue *q1 = init_robocol_queue(8);
    queue *q2 = init_robocol_queue(8);
    queue *q3 = init_robocol_queue(8);
    enqueue(q1, 5);
    display_queue(q1);
    
    while(1){
	
    }


	/*
    command* c = init_command("ZAS", "PWD", "");
    display_command(c);
    destroy_command(c);
    display_command(c);
    */

    //float list[] = {1.0, 2.0, 3.0};
    int val = 0;

    //printf("%s\n", format_string("name", list, sizeof(list) / sizeof(list[0])));

    //format_string("name", list, sizeof(list) / sizeof(list[0]), &val);

    printf("%s\n", get_command_response("SEN", &val));
	uart_close();
}
