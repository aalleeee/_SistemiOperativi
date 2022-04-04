#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
  printf("$$ = ");
  fflush(stdout);
  system("echo $$"); // subshell
  printf(" PID: %d PPID: %d\n", getpid(), getppid());
  return 0;
}
