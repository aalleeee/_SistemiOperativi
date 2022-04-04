// Avendo come argomenti dei “binari”, si eseguono con exec ciascuno in un sottoprocesso (*)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  for (int i = 1; i < argc; i++)
  {
    int fid = fork();
    if(fid != -1)
    {
      //no error, new process
      char * argList[] = {argv[i],NULL}; //Define arguments
      execv(argv[i], argList); //Launch binary
    }
  }
  while(wait(NULL)>0);
  
  return 0;
}
