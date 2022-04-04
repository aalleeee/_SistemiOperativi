#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
int main()
{
  int wid, st, r;
  int fid = fork();             // Generate child

  srand(time(NULL));            // Initialise random
  r = rand() % 256;             // Get random
  
  if (fid == 0)
  {
    // If it is child
    printf("Child... (%d)", r);
    fflush(stdout);
    sleep(3);                   // Pause execution for 3 seconds
    printf(" done!\n");
    exit(r);                    // Terminate with random signal
  }
  else
  {
    // If it is parent
    printf("Parent...\n");
    wid = wait(&st);            // wait for ONE child to terminate
    printf("...child’s id: %d==%d (st=%d)\n", fid, wid, WEXITSTATUS(st));
  }
}