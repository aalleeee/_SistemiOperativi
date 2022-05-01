// Generare un figlio per ogni argomento ed eseguirlo come comando (es.: ./execvp pwd ls) con stdout “normale”

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  int f;
  char command[256];
  char *lst[2];
  
  for(int i = 1; i < argc; i++)
  {
    printf("%d) Command : '%s' [%d]\n", i,argv[i],getpid());
    fflush(stdout);

    f = fork();
    if(f < 0)
    {
      // error
      printf("Fork error\n");
      exit(1);
    }
    else if(f == 0)
    {
      // child
      printf("*Child* [%d] execute command '%s'\n", getpid(), argv[i]);
      fflush(stdout);
      strcpy(command,argv[i]);
      lst[0] = command;
      lst[1] = NULL;
      execvp(command,lst);
    }
  }
  while (wait(NULL)> 0);
  return 0;
}