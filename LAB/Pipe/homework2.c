/*

Impostare una comunicazione bidirezionale tra due processi estendendo il caso a mo’ di “ping-pong”, fino a un messaggi convenzionale di “fine comunicazione”

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "string.h"
#include <stdlib.h>

#define READ 0
#define WRITE 1

int main()
{
  while (true)
  {
    /* code */

    int pipe1[2], pipe2[2];
    char buf[256];
    pipe(pipe1);
    pipe(pipe2); // Create two unnamed pipe

    int p2 = !fork();

    if (p2)
    {
      close(pipe1[WRITE]);
      close(pipe2[READ]);
      int r = read(pipe1[READ], &buf, 50); // Read from pipe
      if (strcmp(buf, "fine comunicazione") == 0)
        exit(1);
      close(pipe1[READ]);

      printf("P2: '%s'\n", buf);
      write(pipe2[WRITE], "Msg from p2", 12); // Writes to pipe
      close(pipe2[WRITE]);
    }

    else
    {
      close(pipe1[READ]);
      close(pipe2[1]);
      write(pipe1[WRITE], "fine comunicazione", 19); // Writes to pipe
      close(pipe1[WRITE]);

      int r = read(pipe2[READ], &buf, 50); // Read from pipe
      if (strcmp(buf, "fine comunicazione") == 0)
        exit(1);
      close(pipe2[READ]);
      printf("P1: ‘%s’\n", buf);
    }
    while (wait(NULL) > 0)
      ;
  }
}

/*
P2 received: 'Msg from p1'
P1 received: ‘Msg from p2’
*/