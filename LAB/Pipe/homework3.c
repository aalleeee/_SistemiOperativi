#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "string.h"
#include <stdlib.h>

/*
Simulazione piping
Realizzare un tool che esegua due comandi (con possibili argomenti) “in piping” avendo un primo parametro “token” da usare come separatore, ad esempio:

./piping pipe ls -alh /tmp pipe wc -l

equivale a:

ls -alh /tmp | wc -l
*/

#define READ 0
#define WRITE 1
#define MAXLEN 256

/*
ERRORS
*/
#define WRONG_ARGS 3
#define WRONG_TOKEN 4
#define FORK_ERR 5

int main(int argc, char **argv)
{
  char token[MAXLEN];
  char *cmd1[MAXLEN], *cmd2[MAXLEN];
  int index = 1;
  int i, j;
  int fd[2]; // pipe

  // min args : program, token, cmd1, token, cmd2 -> 5
  if (argc < 5)
  {
    printf("Missing args\n");
    exit(WRONG_ARGS);
  }

  // get first token
  strcpy(token, argv[index]);
  index++;

  // get first cmd
  i = 0;
  cmd1[i] = argv[index];

  for (; index < argc && strcmp(argv[index], token) != 0; i++)
  {
    cmd1[i] = argv[index];
    index++;
  }

  cmd1[i++] = NULL;

  // check if other token is present
  if (index == argc)
  {
    printf("Missing token\n");
    exit(WRONG_TOKEN);
  }

  index++;

  j = 0;
  cmd2[j] = argv[index];

  // TO DO :: if second token is present but cmd2 empty ??

  // get second cmd
  for (; index < argc && strcmp(argv[index], token) != 0; j++)
  {
    cmd2[j] = argv[index];
    index++;
  }
  cmd2[j++] = NULL;

  // ---------------

  printf("%d  -  %d\n", i, j);

  for (int a = 0; a < i; a++)
  {
    fprintf(stderr, "cmd1[%d]=%s\n", a, cmd1[a]);
  };
  for (int a = 0; a < j; a++)
  {
    fprintf(stderr, "cmd2[%d]=%s\n", a, cmd2[a]);
  };

  pipe(fd); // Create unnamed pipe
  int f = !fork();
  if (f < 0)
  {
    printf("Fork error\n");
    exit(FORK_ERR);
  }
  if (f > 0)
  {
    // parent
    // WRITE
    close(fd[READ]);
    dup2(fd[WRITE], 1);
    close(fd[WRITE]);
    execvp(cmd1[0], (char *const *)cmd1);
  }
  else
  {
    // child
    // READ
    close(fd[WRITE]);
    dup2(fd[READ], 0);
    close(fd[READ]);
    execvp(cmd2[0], (char *const *)cmd2);
  }

  return 0;
}
