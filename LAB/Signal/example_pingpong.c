// Esempio di un ping-pong di messaggi tra un processo padre e un processo figlio
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// errors codes
#define E_FORK 3

int count = 0; // global

void myHandler(int sigNum)
{
  count++;
  printf("Process [%d] , count = %d\n", getpid(), count);
}

int main(int argc, char const *argv[])
{
  signal(SIGUSR1, myHandler);

  int f = fork();
  if (f < 0)
  {
    printf("Fork error\n");
    exit(E_FORK);
  }
  else if (f == 0)
  {
    // child
    while (1)
    {
      printf("Child [%d] (parent is [%d])\n", getpid(), getppid());
      sleep(1);
      kill(getppid(), SIGUSR1);
      pause();
    }
  }
  else
  {
    // parent
    while (1)
    {
      printf("Parent is [%d] (child is [%d])\n", getpid(), f);
      pause();
      sleep(1);
      kill(f, SIGUSR1);
    }
  }

  return 0;
}

/*
Parent is [1002] (child is [1003])
Child [1003] (parent is [1002])
Process [1002] , count = 1
Parent is [1002] (child is [1003])
Process [1003] , count = 1
Child [1003] (parent is [1002])
Process [1002] , count = 2
Parent is [1002] (child is [1003])
Process [1003] , count = 2
Child [1003] (parent is [1002])
Process [1002] , count = 3
Parent is [1002] (child is [1003])
Process [1003] , count = 3
Child [1003] (parent is [1002])
*/
