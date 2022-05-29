#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "string.h"
#include <stdlib.h>

#define MAXSLAVE 10

int idx = -1;
struct sigaction sa;
void print_counter();

typedef enum
{
  false,
  true
} bool;

// check if application run in foreground
bool foreground()
{
  bool fg = false;
  if (getpgrp() == tcgetpgrp(STDOUT_FILENO))
    fg = true;
  return fg;
}

typedef struct Message
{
  int pid;
  int sig1;
  int sig2;
} message;

message report[MAXSLAVE];

void refresh_counter(int tpid, int signum)
{
  // printf("-%d\n",tpid);
  int found = -1;
  for (int i = 0; i < MAXSLAVE && found == -1; i++)
  {
    if (report[i].pid == tpid)
      found = i;
  }
  if (found != -1)
    printf("-%d\n", found);

  if (found == -1)
  { // new one
    idx++;
    report[idx].sig1 = 0;
    report[idx].sig2 = 0;
    report[idx].pid = tpid;
  }
  else
    idx = found;

  if (signum == SIGUSR1)
    report[idx].sig1++;
  else if (signum == SIGUSR2)
    report[idx].sig2++;

  // print_counter();
}

void print_counter()
{
  printf("*********** REPORT ***********\n");
  for (int i = 0; report[i].pid != NULL; i++)
  {
    printf("  PID [%i] -> (%i) SIGURS1 - (%i) SIGURS2\n", report[i].pid, report[i].sig1, report[i].sig2);
  }
  printf("******************************\n");
}

void report_handler(int signum)
{
  // refresh_counter(getpid(), signum);
  print_counter();
  exit(0);
}

void feed_handler(int signum, siginfo_t *info, void *ctx)
{
  if (foreground())
  {
    printf("\n  Foreground program receive signal %d\n", signum);
  }
  if (signum == SIGUSR1 || signum == SIGUSR2)
  {
    int sender=(int)info->si_pid;
    refresh_counter(sender, signum);
  }
  else if (signum == SIGINT || signum == SIGTERM)
  {
    print_counter();
    exit(0);
  }
}

int main(int argc, char const *argv[])
{
  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = feed_handler;
  sigaction(SIGUSR1, &sa, NULL);
  sigaction(SIGUSR2, &sa, NULL);
  sigaction(SIGINT, &sa, NULL);
  sigaction(SIGTERM, &sa, NULL);

  printf("-----------------------\n");
  printf("My PID is %d\n", getpid());
  printf("-----------------------\n");

  while (1)
  {
    /* code */
  }

  print_counter();

  return 0;
}
