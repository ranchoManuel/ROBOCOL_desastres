#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PADDING 10000000

void print_array();

int length;
char** cpy;

int main (int argc, char *argv[])
{
	cpy = malloc(argc * PADDING * sizeof(char));
	length = argc;

	int i = 0;
	for(; i < length; i++)
	{
    	*(cpy + i) = malloc(sizeof(char) * (strlen(*(argv + i))));
    	strcpy(*(cpy + i), *(argv + i));
	}
	

	print_array();
	return 0;
 }

void print_array()
{
	int i = 0;
	for(; i < length; i++)
		printf("%s\n", *(cpy + i));
}
