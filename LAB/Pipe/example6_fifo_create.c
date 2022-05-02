#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
  char *fifoName = "fifo1";
  mkfifo(fifoName, S_IRUSR | S_IWUSR); // Create pipe if it doesn’t exist
  perror("Created?");

  if (fork() == 0)
  {
    // Child
    open(fifoName, O_RDONLY); // Open READ side of pipe...stuck!
    printf("Open read\n");
  }
  
  else
  {
    sleep(1);
    open(fifoName, O_WRONLY); // Open WRITE side of pipe
    printf("Open write\n");
  }
}

/*
Created?: Success
Open write
Open read
*/