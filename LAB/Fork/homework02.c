// Avendo come argomenti dei “binari”, si eseguono con exec ciascuno in un sottoprocesso ma in più salvando i flussi di stdout e stderr in un unico file
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char** argv) {

  int fd = open("temp.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  dup2(fd,1); // stdout
  dup2(fd,2); // stderr
  for(int i = 1; i < argc; i++)
  {
    int f = fork();
    if(f == 0)
    {
      //printf("New child\n");
      char * par[] = {argv[i],NULL};
      execvp(argv[i],par);
    }
  }
  while (wait(NULL)>0);
  close(fd);
  
  return 0;
}