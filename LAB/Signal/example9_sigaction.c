#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int signo)
{
  printf("signal %d received\n", signo);
  sleep(2);
  printf("Signal done\n");
}

int main()
{
  printf("Process id: %d\n", getpid());
  struct sigaction sa;
  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask); // Use an empty mask → block no signal
  sigaction(SIGUSR1, &sa, NULL);
  while (1)
    ;
}