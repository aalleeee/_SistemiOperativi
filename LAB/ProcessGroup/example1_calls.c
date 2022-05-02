#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 

int main(void)
{
  int isChild = !fork(); // new child
  printf("PID %d PPID: %d GID %d\n", getpid(), getppid(), getpgid(0));

  if (isChild)
  {
    isChild = !fork(); // new child
    if (!isChild)
      setpgid(0, 0); // Become group leader
    sleep(1);
    fork(); // new child
    printf("PID %d PPID: %d GID %d\n", getpid(), getppid(), getpgid(0));
    sleep(1);
  }
  
  while (wait(NULL) > 0)
    ;
}

/*
PID 358 PPID: 13 GID 358
PID 359 PPID: 358 GID 358
PID 359 PPID: 358 GID 359
PID 360 PPID: 359 GID 358
PID 362 PPID: 360 GID 358
PID 361 PPID: 359 GID 359
*/