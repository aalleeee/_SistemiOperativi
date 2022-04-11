//Basic use of custom handler

#include <signal.h> 
#include <stdio.h>
#include <stdlib.h>
void myHandler(int sigNum)
{
  printf("CTRL+Z\n");
  exit(2);
}
int main(void)
{
  signal(SIGTSTP, myHandler);
  while (1);
}

// if you press CTRL+Z (terminal stop) singal calls custom handler that prints "CTRL+Z"