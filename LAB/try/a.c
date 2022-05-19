// Avendo come argomenti dei “binari”, si eseguono con exec ciascuno in un sottoprocesso
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define LEN 256

int main(int argc, char *argv[])
{
  if (argc == 3)
  {
    int fd;
    int f = fork();
    if (f < 0)
    {
      exit(3);
    }
    if (f == 0)
    {
      // child
      fd = open("test.txt", O_WRONLY);
      dup2(fd, 1);
      char *par1[] = {argv[1], NULL};
      execvp(argv[1], par1);
      close(fd);
    }
    else
    {
      wait(NULL);
      fd = open("test.txt", O_RDONLY);
      dup2(fd, 0);
      char *par2[] = {argv[2], NULL};
      execvp(argv[2], par1);
      close(fd);
    }
  }
  return 0;
}
