// Generare N figli che restituiscono al padre un numero casuale (da 0 a 255 compresi), il quale mostra poi il minimo e il massimo con i “pid” corrispondenti

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

int N = 10;

int main()
{
  int f, n_rand, w, s, c;
  int min = 256;
  int max = -1;
  int min_pid, max_pid;
  
  for (int i = 0; i < N; i++)
  {
    f = fork();
    if (f < 0)
    {
      // error
      printf("Error during [Fork]\n");
      exit(1);
    }
    else if (f == 0)
    {
      // child
      srand(time(NULL) + getpid());
      n_rand = rand() % 256;
      printf("*Child* [%d] generate: %d\n", getpid(), n_rand);
      exit(n_rand);
    }
  }

  while ((w = wait(&s)) > 0) // attende la conclusione di UN figlio e ne restituisce il PID riportando lo status nel puntatore passato come argomento
  {
    c = WEXITSTATUS(s); // restituisce lo stato vero e proprio (ad esempio il valore usato nella “exit”)
    printf("*Parent* child [%d] with status %d\n", w, c);
    if (c < min)
    {
      min = c;
      min_pid = w;
    }
    if (c > max)
    {
      max = c;
      max_pid = w;
    }
  }

  printf("\n\nMin: %d with pid %d \nMax: %d with pid %d\n", min, min_pid, max, max_pid);
  return 0;
}