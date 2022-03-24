#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void *tbody(void *arg)
 {
    int j;

     printf("ciao sono un thread, mi hanno appena creato\n");
     *(int *)arg = 10;
     sleep(5); /* faccio aspettare un pò il mio creatore, poi termino */
     pthread_exit((int *)50); /* oppure return ((int *)50); */
}


main(int argc, char **argv)
{

 int i;
 pthread_t mythread;
 void *result;

 i=1;
 printf("i=%d \n", i);
 printf("sono il primo thread, ora ne creo un altro \n");
 pthread_create(&mythread, NULL, tbody, (void *) &i);
 printf("ora aspetto la terminazione del thread che ho creato \n");
 pthread_join(mythread, &result);

 printf("Il thread creato ha assegnato %d ad i\n",i);
 printf("Il thread ha restituito %d \n", result);
}

