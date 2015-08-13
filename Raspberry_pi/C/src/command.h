/*
	command.h

	autor: Sebastián Valencia
	email: sc.valencia606@gmail.com
*/

/*
	Un comando es un identificador en cadena de texto, y máximo un par de argumentos
*/
	
typedef struct command {
    char* name;
    char* arg1;
    char* arg2;
} command;

/*
	Las siguientes funciones o procedimientos, definen las operaciones de un comando
*/
command* init_command(char*, char*, char*);
int get_priority(command*);
void display_command(command*);
void destroy_command(command*);
char* command_string(command*);