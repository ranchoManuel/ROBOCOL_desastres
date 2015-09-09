#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define NUM_THREADS 2

int continuar=TRUE;

pthread_t tid[NUM_THREADS];

void* doSomeThing(void *arg)
{
	clock_t begin;
  pthread_t id = pthread_self();
  int numSecs;

	while(continuar)
	{
		if(pthread_equal(id,tid[0]))
		{
			printf("\n First thread processing\n");
			numSecs=1;
		}
		else
		{
		    printf("\n Second thread processing\n");
		    numSecs=2;
		}
		begin = clock();
		while(((clock()-begin)/CLOCKS_PER_SEC)<numSecs);
	}
    return NULL;
}

int main(void)
{
	int err, i;

	//Aqui se crean los threads
  for(i=0; i < NUM_THREADS; i++)
  {
    err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
    if(err != 0) printf("\ncan't create thread :[%s]", strerror(err));
    else printf("\n Thread created successfully\n");
  }

  //Se deja un tiempo muerto para ver la ejecucion
  puts("__________________________________");

  sleep(5);
  continuar=FALSE;
  return 0;
}
