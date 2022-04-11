//Basic example of kill() to send signal

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void myHandler(int sigNum)
{
  printf("[%d]ALARM!\n", getpid());
}

int main(void)
{
  signal(SIGALRM, myHandler);

  int child = fork();
  if (!child)
    while (1); // block the child
  
  printf("[%d]sending alarm to %d in 3 s\n", getpid(), child);
  sleep(3);
  kill(child, SIGALRM); // send ALARM, child’s handler reacts

  printf("[%d]sending SIGTERM to %d in 3 s\n", getpid(), child);
  sleep(3);
  kill(child, SIGTERM); // send TERM: default is to terminate

  while (wait(NULL) > 0);
}

// output:
// [7374]sending alarm to 7375 in 3 s     -> kill 1 from child with SIGALRM that recall myHandler (*)
// [7374]sending SIGTERM to 7375 in 3 s   -> kill 2 from child 
// [7375]ALARM!                           -> (*) handler call from father after child terminate