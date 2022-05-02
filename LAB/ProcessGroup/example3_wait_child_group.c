#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
  int group1 = fork();
  int group2;

  if (group1 == 0)
  {                       // First child
    setpgid(0, getpid()); // Become group leader
    fork();
    fork(); // Generated 4 children in new group
    sleep(2);
    return 0; // Wait 2 sec and exit
  }
  
  else
  {
    group2 = fork();
    if (group2 == 0)
    {
      setpgid(0, getpid()); // Become group leader
      fork();
      fork(); // Generated 4 children
      sleep(4);
      return 0; // Wait 4 sec and exit
    }
  }
  
  sleep(1); // make sure the children changed their group

  while (waitpid(-group1, NULL, 0) > 0)
    ;
  printf("Children in %d terminated\n", group1);
  
  while (waitpid(-group2, NULL, 0) > 0)
    ;
  printf("Children in %d terminated\n", group2);

}

/*
Children in 533 terminated
Children in 534 terminated
*/