#include <signal.h>
#include <unistd.h>
#include <stdio.h>

sigset_t mod, old;
int i = 0;

void myHandler(int signo)
{
  printf("signal received\n");
  i++;
}

int main()
{
  printf("my id = %d\n", getpid());
  signal(SIGUSR1, myHandler);
  sigemptyset(&mod); // Initialise set
  sigaddset(&mod, SIGUSR1);
  while (1)
    if (i == 1)
      sigprocmask(SIG_BLOCK, &mod, &old);
}
