#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_LEN 256

char filename[MAX_LEN];
char string[MAX_LEN];
int idx;
int pids[MAX_LEN];
int stop = 0;
int main_pid;

void handler(int signum)
{
  int fd, r;
  char content[MAX_LEN];
  if (getpid() == main_pid)
  {
    if (signum == SIGUSR1)
    {
      fd = open(filename, O_RDONLY);
      if (fd < 0)
      {
        printf("Error file\n");
        exit(5);
      }
      r = read(fd, content, MAX_LEN);
      if (r < 0)
      {
        printf("Error reading file\n");
        exit(6);
      }
      idx = atoi(content);
      kill(pids[idx - 1], SIGUSR2);
    }
  }
  else
  {
    if (signum == SIGUSR2)
    {
      printf("<<<<<<< %d --- %s\n", idx, string);
      stop = 1;
    }
  }
}

int main(int argc, char const *argv[])
{

  int n;
  int i, c, f;
  main_pid = getpid();

  printf("****Main pid: [%d]*****\n", main_pid);

  if (argc < 3)
  {
    printf("Error arguments\n");
    exit(3);
  }
  strcpy(filename, argv[1]);
  n = argc - 2;
  // printf("Filename: %s, n: %d", filename, n); //*

  for (i = 0; i < n; i++)
  {
    c = i + 1;
    f = fork();
    if (f < 0)
    {
      printf("Error fork\n");
      exit(4);
    }
    else if (f == 0)
    {
      // child
      idx = c;
      strcpy(string, argv[c]);

      signal(SIGUSR2, handler);
      while (stop == 0)
        ;
      exit(0);
    }
  }

  // main process
  signal(SIGUSR1, handler);
  while (wait(NULL) > 0)
    ;

  return 0;
}
