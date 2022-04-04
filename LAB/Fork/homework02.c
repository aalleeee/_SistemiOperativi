// Avendo come argomenti dei “binari”, si eseguono con exec ciascuno in un sottoprocesso (*)
// in più salvando i flussi di stdout e stderr in un unico file (*)
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  
  int fo = open("file.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  dup2(fo,1); //stdout
  dup2(fo,2); //stderr
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
  close(fo);
  return 0;
}
