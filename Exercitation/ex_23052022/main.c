#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <termios.h>
#include "string.h"

#define N 10

FILE *file;
int action = -1;
int idx = -1;
int pids[N];
int cont = 0;

typedef enum
{
  KP_ECHO_OFF,
  KP_ECHO_ON,
} kp_echo_t;
int keypress(const kp_echo_t echo)
{
  struct termios savedState, newState;
  unsigned char echo_bit; // flag
  int c;
  if (-1 == tcgetattr(STDIN_FILENO, &savedState))
  {
    return EOF;
  }; // error
  newState = savedState;
  if (KP_ECHO_OFF == echo)
  {
    echo_bit = ECHO;
  }
  else
  {
    echo_bit = 0;
  };
  /* canonical input + set echo with minimal input as 1. */
  newState.c_lflag &= ~(echo_bit | ICANON);
  newState.c_cc[VMIN] = 1;
  if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &newState))
  {
    return EOF;
  };             // error
  c = getchar(); /* block until key press */
  if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &savedState))
  {
    return EOF;
  }; // error
  return c;
}

void handler_server(int signum)
{
  if (signum == SIGUSR1)
    action = 1;
  if (signum == SIGUSR2)
    action = 2;
  if (signum == SIGINT)
  {
    fprintf(file, "%d\n", idx + 1);
    fflush(file);
    exit(0);
  }
}

int main(int argc, char const *argv[])
{
  if (argc < 3)
  {
    printf("E: args\n");
    exit(3);
  }
  if (strcmp(argv[1], "server") == 0)

    // server
    if (fopen(argv[2], "r"))
    {
      printf("E: file\n");
      exit(4);
    }
    else
    {
      file = fopen(argv[2], "w+");
      fprintf(file, "%d\n", getpid());
      fflush(file);
      printf("[server:%d]\n", getpid());
      fflush(NULL);
      signal(SIGINT, handler_server);
      signal(SIGUSR1, handler_server);
      signal(SIGUSR2, handler_server);
      while (1)
      {
        if (action == 1)
        {
          int f = fork();
          {
            if (f == 0)
            {
              // child
              fprintf(file, "+%d\n", getpid());
              fflush(file);
              printf("[server] +%d\n", getpid());
              fflush(NULL);
            }
            else if (f > 0)
            {
              idx++;
              pids[idx] = f;
            }
          }
          action = -1;
        }
        else if (action == 2)
        {
          if (idx >= 0)
          {
            kill(pids[idx], SIGKILL);
            fprintf(file, "-%d\n", pids[idx]);
            fflush(file);
            printf("[server] -%d\n", pids[idx]);
            fflush(NULL);
            idx--;
          }
          else
          {
            fprintf(file, "0\n");
            fflush(file);
            printf("[server] 0\n");
            fflush(NULL);
          }
          action = -1;
        }
      }
    }
  else if (strcmp(argv[1], "client") == 0)
  {
    int open = 0;
    int spid;
    while (open == 0)
    {
      file = fopen(argv[2], "r");
      if (file != NULL)
      {
        open = 1;
        fscanf(file, "%d", &spid);
        printf("[client] server: %d\n", spid);
        fflush(NULL);
      }
    }
    char c;
    while (1)
    {
      c = keypress(KP_ECHO_OFF); // read single keypress without echoing
      if (c == '+')
      {
        kill(spid, SIGUSR1);
        if (cont < 10)
          cont++;
        printf("[client] %d\n", cont);
        fflush(NULL);
      }
      if (c == '-')
      {
        kill(spid, SIGUSR2);
        if (cont > 0)
          cont--;
        printf("[client] %d\n", cont);
        fflush(NULL);
      }
      if (c == '\n')
      {
        for (int i = 0; i < cont; i++)
        {
          kill(spid, SIGUSR2);
          sleep(1);
          printf("[client] %d\n", cont);
          fflush(NULL);
        }
        kill(spid, SIGINT);
        exit(0);
      }
    }
  }
  else
  {
    printf("E: argv[1]\n");
    exit(4);
  }
  return 0;
}
