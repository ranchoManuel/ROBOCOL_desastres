#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define TRUE 1
#define FALSE 0

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

int continuar=TRUE;

pthread_t tid[2];

void* doSomeThing1(void *arg)
{
	clock_t begin;

	while(continuar)
	{
		printf(KRED "\n First thread processing\n" RESET);
		
		begin = clock();
		while(((clock()-begin)/CLOCKS_PER_SEC)<1);
	}
    return NULL;
}

void* doSomeThing2(void *arg)
{
	clock_t begin;

	while(continuar)
	{
		printf(KGRN "\n Second thread processing\n" RESET);
		
		begin = clock();
		while(((clock()-begin)/CLOCKS_PER_SEC)<2);
	}
    return NULL;
}

int main(void)
{
    int err;

	//Aqui se crean los threads
    err = pthread_create(&(tid[0]), NULL, &doSomeThing1, NULL);
    if(err != 0) printf("\ncan't create thread 1:[%s]", strerror(err));
    else printf("\n Thread 1 created successfully\n");
    
    err = pthread_create(&(tid[1]), NULL, &doSomeThing2, NULL);
    if(err != 0) printf("\ncan't create thread 2:[%s]", strerror(err));
    else printf("\n Thread 2 created successfully\n");
    
    //Se deja un tiempo muerto para ver la ejecucion  
    puts("__________________________________");
      
    sleep(5);
    continuar=FALSE;
    return 0;
}
