#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "robocol_list.h"

#define MEMORY_OVERFLOW -9
#define EMPTY -1

node* init_robocol_list() {
	node *new_list;
	new_list = (node *) malloc(sizeof(node));
	new_list->data = (int) NULL;
	new_list->next = (node *) malloc(sizeof(node));
	return new_list;
}

int append(listPointer *sPointer, int value) {
	node* newPtr, prevPtr, currentPtr;
	newPtr = (node *) malloc(sizeof(node));

	if(newPtr != NULL) {
		newPtr->data = value;
		newPtr->next = NULL;

		prevPtr = NULL;
		currentPtr = *sPointer;

		while(currentPtr != NULL) {
			prevPtr = currentPtr;
			currentPtr = currentPtr->next;
		}

		if(prevPtr == NULL) {
			newPtr->next = *sPointer;
			*sPointer = newPtr;
		}
		else {
			prevPtr->next = newPtr;
			newPtr->next = currentPtr;
		}
		return 1;
	}
	else {
		return MEMORY_OVERFLOW;
	}
}

/*
int delete(listPointer *, int) {
	return 0;
}
*/

bool empty_list(listPointer current) {
	return(current == NULL);
}

void display_list(listPointer current) {
	if(current == NULL)
		printf("\n");
	else {
		while(current != NULL) {
			printf("%d -> ", current->data);
			current = current->next;
		}
		printf("NULL\n\n");
	}
}