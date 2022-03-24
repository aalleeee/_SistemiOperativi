#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

// esempio di utlizzo pipe con nome
// legato a p4.c

int main()
{
  //con pipe con nome viene creato riferimento nel filesystem che appare come file ma è una pipe, è una referenza nel filesystem

  key_t key;
  int i, a;
  int shm, shm1;
  char *addr, *addr1;
  struct shmid_ds buf;

  //si una pathname come key per la shmget()
  key = ftok("pathname", 3);
  printf("key=%d\n", key);

  shm1 = shmget(key, 100, IPC_CREAT + S_IRUSR + S_IWUSR);
  addr1 = shmat(shm1, NULL, 0);
  sprintf(addr1, "P3 wrote cccccccccccccccccccccccccccccccccccccccccccc");

  printf("P3: identifier of the shared memory shm1= %d\n", shm1);

  shmdt(addr1);
  /*
     shmctl(shm1,IPC_RMID,0);
  */
}
