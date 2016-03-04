//BASADO EN: https://www.gidforums.com/t-3369.html
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 110

int main()
{
  //Para poder parar el proceso
  char buffWrite  [BUFFSIZE];
  char buffRead   [BUFFSIZE];

  pid_t pid1, pid2;
  int rv;
  int	commpipe[2];	/* This holds the fd for the input & output of the pipe */

  /* Setup pipeline comunicacion*/
  if(pipe(commpipe)) {fprintf(stderr,"Pipe error!\n");exit(1);}

  /* Attempt to fork and check for errors */
  if((pid1=fork()) == -1) {fprintf(stderr,"Fork error. Exiting.\n"); exit(1);}

  if(pid1) //PROCESO PADRE
  {
    dup2(commpipe[1],1);	/* Replace stdout with out side of the pipe */
    close(commpipe[0]);	/* Close unused side of pipe (in side) */

    setvbuf(stdout,(char*)NULL,_IONBF,0);	/* Set non-buffered output on stdout */

    while(1)
    {
      fflush(stdout);
      fgets(buffWrite, BUFFSIZE, stdin);
      //Es necesario quitarle el ultimo caracter porque es un enter '\n'
      buffWrite[strlen(buffWrite)-1] = '\0';
      if(strcmp("N", buffWrite)==0)
      {
        printf("q\n");
        wait(&rv);
        fprintf(stderr,"Child exited with a %d value\n",rv);
        break;
      }
      else if(strcmp("q", buffWrite)==0)
      {
        printf("q\n");
        wait(&rv);
        fprintf(stderr,"Child exited with a %d value\n",rv);
      }
      else
      {
        printf("%s\n", buffWrite);
        printf("q\n");
        wait(&rv);
        fprintf(stderr,"Child exited with a %d value\n",rv);
      }
    }
    fprintf(stderr,"SALE\n");
  }
  else //PROCESO HIJO
  {
    /* A zero PID indicates that this is the child process */
    dup2(commpipe[0],0);	/* Replace stdin with the in side of the pipe */
    close(commpipe[1]);	/* Close unused side of pipe (out side) */

    char *losArgs[] = { "ffmpeg", "-loglevel", "panic", "-i", "/dev/video0", "-s", "640x480", "-pix_fmt", "yuv420p", "-r", "10", "-fflags", "nobuffer", "-an", "-f", "mpegts", "udp://127.0.0.1:10000", NULL };
    char *comnd1="ffmpeg -loglevel panic -i /dev/video0 -s 640x480 -pix_fmt yuv420p -r 10 -fflags nobuffer -an -f mpegts udp://127.0.0.1:10000";
    char *comnd2="ffmpeg -loglevel panic -i /dev/video1 -s 640x480 -pix_fmt yuv420p -r 10 -fflags nobuffer -an -f mpegts udp://127.0.0.1:10000";

    char c;
    while(1)
    {
      scanf("%c", &c);
      system("killall ffmpeg");

      if(c=='1')
      {
        system(comnd1);
      }
      else if(c=='2')
      {
        system(comnd2);
      }
    }

  }
  return 0;
}
