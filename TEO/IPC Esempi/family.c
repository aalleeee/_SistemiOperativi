#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// esempio 1 di Inter Process Communications (IPC): shared memory segment
// esempio di utlizzo di shared memory segment (memoria condivisa per comunicazione tra pocessi)

int *shared;
int shmid, pid;

int main()
{
  int s, i;

  // shmget() ritorna l'id del segmento di memoria appena creato
  // IPC_PRIVATE identifica la chiave per forzare il segmento ad essere disponibile solo per processi di tipo padre-figlio
  // 0600 rappresenta i permessi (in questo caso lettura + scrittura)
  shmid = shmget(IPC_PRIVATE, sizeof(int), 0600);
  printf("shmid=%d\n", shmid);

  // shmat(): attachment del segmento condiviso
  shared = shmat(shmid, 0, 0);
  // processo (padre) scrive sul segmento condiviso "100"
  *shared = 100;

  printf("%d\n", *shared);
  pid = fork();

  if (pid == 0) // son
  {
    // il figlio scrive nel segmento condiviso "1000"
    *shared = 1000;
    // shmdt() detachment del segmento condiviso
    shmdt((const void *)shared);
  }
  else // father
  {
    // padre aspetta terminazione del figlio
    wait(&s);
    printf("%d\n", *shared); // (ora vale 1000)
    // shmdt() detachment del segmento condiviso
    shmdt((const void *)shared);
    // con il secondo paramentro (IPC_RMID) shmctl() rimuove il segmento condiviso creato
    shmctl(shmid, IPC_RMID, 0);
  }
  return 0;
}

// to compile: gcc -pthread -o family family.c
