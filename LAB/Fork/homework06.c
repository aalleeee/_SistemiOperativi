// Generare due figli per due argomenti ed eseguirli in modo da avere l’effetto del piping bash attraverso però un file su disco (es.: … ls wc come se fosse ls | wc)

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const **argv)
{
  int f;
  int file_d;
  char command[256];
  char *lst[2];

  if (argc != 3)
  {
    printf("Wrong num params passed\n");
    exit(1);
  }

  f = fork();
  if (f < 0)
  {
    // error
    printf("Fork error\n");
    exit(2);
  }

  if (f == 0)
  {
    // child 1
    file_d = open("temp.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    dup2(file_d, 1);
    close(file_d);
    strcpy(command, argv[1]);
    lst[0] = command;
    lst[1] = NULL;
    execvp(command, lst);
  }
  while (wait(NULL) > 0)
    ;

  f = fork();

  if (f < 0)
  {
    // error
    printf("Fork error\n");
    exit(2);
  }

  if (f == 0)
  {
    // child 2
    file_d = open("temp.txt", O_RDONLY, S_IRUSR | S_IWUSR);
    dup2(file_d, 0);
    close(file_d);
    strcpy(command, argv[2]);
    lst[0] = command;
    lst[1] = NULL;
    execvp(command, lst);
  }
  while (wait(NULL) > 0)
    ;

  return 0;
}
