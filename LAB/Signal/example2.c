// Basic use of custom handler with different signals

#include <signal.h> 
#include <stdio.h>
#include <stdlib.h>

void myHandler(int sigNum)
{
  if (sigNum == SIGINT)
    printf("CTRL+C\n");
  else if (sigNum == SIGTSTP)
    printf("CTRL+Z\n");
  exit(2);
}

int main(int argc, char const *argv[])
{
  signal(SIGINT, myHandler);
  signal(SIGTSTP, myHandler);
  while (1);
  return 0;
}

// one custom handler 2 singal
// if you press CTRL+Z (terminal stop) singal calls custom handler that prints "CTRL+Z"
// if you press CTRL+C (terminal interrupt) singal calls custom handler that prints "CTRL+C"