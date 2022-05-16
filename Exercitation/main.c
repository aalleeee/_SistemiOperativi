#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "string.h"
#include <stdlib.h>

#define LEN 255
int n;
int idx = 0;
int *pids;

void f_handler(int signum)
{
  printf("kill %d\n",getpid());
  exit(0);
}

void m_hander(int signum)
{
  printf("**\n");
  if (idx <= n)
  {
    //printf("*******\n");
    //printf("*******\n");
    //printf("idx: %d\n", idx);
    printf("call kill %d\n",pids[idx]);
    fflush(NULL);
    kill(pids[idx], SIGUSR2);
    idx++;
  }
}

int main(int argc, char const *argv[])
{

  char target[LEN];

  if (argc != 3)
  {
    exit(3);
  }

  strcpy(target, argv[1]);
  n = atoi(argv[2]);
  if (!(n >= 1 && n <= 10))
    exit(4);

  pids = new int[n];

  FILE *f = fopen(target, "wx");
  if (f <= 0)
  {
    exit(5);
  }

  //  fwrite(buf,255,255,f);

  fprintf(f, "Parent %d\n", getpid());
  fflush(f);
  int k = fork();
  {
    if (k < 0)
    {
      exit(6);
    }
    if (k == 0)
    {
      // manager
      signal(SIGUSR1, m_hander);
      fprintf(f, "Child %d\n", getpid());
      fflush(f);
      for (int i = 0; i < n; i++)
      {
        k = fork();
        if (k < 0)
        {
          exit(7);
        }
        if (k == 0)
        {
          // foglie
          signal(SIGUSR2, f_handler);
          fprintf(f, "Foglia %d\n", getpid());
          fflush(f);
          sleep(60000);
          exit(0);
        }
        else
        {
          // manager
          pids[i] = k;
        }
      }
      while (wait(NULL) > 0)
        ;
    }
    else
    {
      // parent
      exit(0);
    }
  }

  fclose(f);

  return 0;
}
