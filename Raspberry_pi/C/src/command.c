/*
	Aqui se define la estructura general de los comandos, esto es su nombre y sus argumentos.
	Asimismo, se define la intercción de los mismos con el ambiente, la definición de sus
	prioridades y su ciclo de vida.

	autor: Sebastián Valencia
	email: sc.valencia606@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "command.h"

#define MAX_ARG_SIZE 3
#define HIGH_PRIORITY 1
#define MEDIUM_PRIORITY 2
#define LOW_PRIORITY 3
#define NO_PRIORITY -1

command* init_command(char* name, char* arg1, char* arg2) {
	command* new_command;
	new_command = (command *) malloc(sizeof(command));
	new_command->name = (char*) malloc(MAX_ARG_SIZE * sizeof(char));
	strcpy(new_command->name, name);
	new_command->arg1 = (char*) malloc(MAX_ARG_SIZE * sizeof(char));
	strcpy(new_command->arg1, arg1);
	new_command->arg2 = (char*) malloc(MAX_ARG_SIZE * sizeof(char));
	strcpy(new_command->arg2, arg2);
	return new_command;
}

int get_priority(command* arg) {
	if(strcmp(arg->name, "SEN") == 0)
		return HIGH_PRIORITY;

	else if(strcmp(arg->name, "CAD") == 0)
		return HIGH_PRIORITY;

	else if(strcmp(arg->name, "MCA") == 0)
		return HIGH_PRIORITY;

	else if(strcmp(arg->name, "MBR") == 0)
		return HIGH_PRIORITY;

	else if(strcmp(arg->name, "TGL") == 0)
		return HIGH_PRIORITY;

	else if(strcmp(arg->name, "TGB") == 0)
		return HIGH_PRIORITY;

	else if(strcmp(arg->name, "ZAR") == 0)
		return HIGH_PRIORITY;

	else if(strcmp(arg->name, "END") == 0)
		return HIGH_PRIORITY;

	else if(strcmp(arg->name, "TER") == 0)
		return HIGH_PRIORITY;

	return NO_PRIORITY;
}

void display_command(command* arg) {
	command* temp = (command*) malloc(sizeof(arg));
	if(temp == NULL)
		return;
	if(strlen(arg->arg1) == 0) {
		printf("%s", arg->name);
	} else {
		printf("%s:%s", arg->name, arg->arg1);
		if(strlen(arg->arg2) != 0)
			printf(":%s", arg->arg2);
	}
	printf(";\n");
}

void destroy_command(command* arg) {
	command* temp = (command*) malloc(sizeof(arg));
	if(temp == NULL)
		return;
	free(arg->name);
	free(arg->arg1);
	free(arg->arg2);
	free(arg);
}

char* command_string(command* arg) {
	static char ans[100];

	if(strcmp(arg->name, "SEN") == 0)
		strcat(ans, arg->name);

	else if(strcmp(arg->name, "CAD") == 0)
		strcat(ans, arg->name);

	else if(strcmp(arg->name, "MCA") == 0) {
		strcat(ans, arg->name);
		strcat(ans, (char*) ';');
		strcat(ans, arg->arg1);
		strcat(ans, (char*) ';');
		strcat(ans, arg->arg2);		
	}

	else if(strcmp(arg->name, "MBR") == 0) {
		strcat(ans, arg->name);
		strcat(ans, (char*) ';');
		strcat(ans, arg->arg1);
		strcat(ans, (char*) ';');
		strcat(ans, arg->arg2);
	}

	else if(strcmp(arg->name, "TGL") == 0)
		strcat(ans, arg->name);

	else if(strcmp(arg->name, "TGB") == 0)
		strcat(ans, arg->name);

	else if(strcmp(arg->name, "ZAR") == 0)
		strcat(ans, arg->name);

	else if(strcmp(arg->name, "END") == 0)
		strcat(ans, arg->name);

	else if(strcmp(arg->name, "TER") == 0)
		strcat(ans, arg->name);

	strcat(ans, (char*) ";");

	return ans;

}