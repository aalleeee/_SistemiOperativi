#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void myHandler(int sigNum)
{
  printf("Continue!\n");
}

int main()
{
  signal(SIGCONT, myHandler);
  signal(SIGUSR1, myHandler);
  pause();
}
