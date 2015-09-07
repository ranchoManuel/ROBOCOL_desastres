typedef struct command
{
    char* name;
    char* arg1;
    char* arg2;
} command;

command* init_command(char*, char*, char*);
int get_priority(command*);
void display_command(command*);
void destroy_command(command*);
char* command_string(command*);