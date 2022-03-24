#include <pthread.h>
#include <stdio.h>

void *tbody(void *arg)
{
  int j;
  printf(" ciao sono un thread, mi hanno appena creato\n");
  *(int *)arg = 10;
  sleep(2);                /* faccio aspettare un pò il mio creatore, poi termino */
  pthread_exit((int *)50); /* oppure return ((int *)50); */
}

int main(int argc, char **argv)
{
  int i;
  pthread_t mythread;
  void *result;
  printf("sono il primo thread, ora ne creo un altro \n");
  pthread_create(&mythread, NULL, tbody, (void *)&i);
  printf("ora aspetto la terminazione del thread che ho creato \n");
  pthread_join(mythread, &result);
  printf("Il thread creato ha assegnato %d ad i\n", i);
  printf("Il thread ha restituito %d \n", result);
  return 0;
}