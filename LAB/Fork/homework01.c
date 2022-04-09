// Avendo come argomenti dei “binari”, si eseguono con exec ciascuno in un sottoprocesso
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{

  for (int i = 1; i < argc; i++)
  {
    int f = fork();
    if (f == 0)
    {
      // printf("New child\n");
      char *par[] = {argv[i], NULL};
      execv(argv[i], par);
    }
  }
  while (wait(NULL) > 0);

  return 0;
}