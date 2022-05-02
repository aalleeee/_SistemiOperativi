#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

void handler(int signo)
{
  printf("[%d,%d] sig%d received\n", getpid(), getpgid(0), signo);
  sleep(1);
  exit(0);
}

int main(void)
{
  signal(SIGUSR1, handler);
  signal(SIGUSR2, handler);
  int ancestor = getpid();
  int group1 = fork();
  int group2;

  if (getpid() != ancestor)
  {
    // First child
    setpgid(0, getpid()); // Become group leader
    fork();
    fork(); // Generated 3 children in new group
  }
  else
  {
    group2 = fork();

    if (getpid() != ancestor)
    {                       // Second child
      setpgid(0, getpid()); // Become group leader
      fork();
      fork();
    }
  } // Generated 3 children in new group

  if (getpid() == ancestor)
  {
    printf("[%d]Ancestor and I'll send signals\n", getpid());
    sleep(1);
    kill(-group2, SIGUSR2); // Send SIGUSR2 to group2
    kill(-group1, SIGUSR1); // Send SIGUSR1 to group1
  }
  else
  {
    printf("[%d,%d]chld waiting signal\n", getpid(), getpgid(0));
    while (1)
      ;
  }
  while (wait(NULL) > 0)
    ;
  
  printf("All children terminated\n");
}

/*
[438]Ancestor and I'll send signals

[439,439]chld waiting signal
[441,439]chld waiting signal
[440,440]chld waiting signal
[443,439]chld waiting signal
[445,440]chld waiting signal
[444,439]chld waiting signal
[442,440]chld waiting signal

[446,440]chld waiting signal
[441,439] sig10 received
[440,440] sig12 received
[439,439] sig10 received
[445,440] sig12 received
[442,440] sig12 received
[443,439] sig10 received
[446,440] sig12 received
[444,439] sig10 received

All children terminated
*/