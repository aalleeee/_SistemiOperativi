#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX_LEN 256

char action[MAX_LEN];
char name[MAX_LEN];
char quote[MAX_LEN];
char q_name[MAX_LEN];

struct msg_buffer
{
  long mtype;
  char mtext[50];
} snd, rcv;

int main(int argc, char const *argv[])
{
  snd.mtype = 1;
  if (argc < 3 || argc > 4)
  {
    printf("Error arguments\n");
    exit(3);
  }
  strcpy(action, argv[1]);
  strcpy(name, argv[2]);
  if (argc == 4)
  {
    strcpy(quote, argv[3]);
    strcpy(snd.mtext, quote);
  }

  // printf("%s\n%s\n%s\n%s\n", action, name, quote, snd.mtext);

  strcpy(q_name, "/tmp/");
  strncat(q_name, name, 100);
  creat(q_name, 0777);

  // printf("%s\n", q_name);

  key_t queueKey = ftok(q_name, 1);
  int queueId;

  if (strcmp(action, "push") == 0)
  {
    queueId = msgget(queueKey, 0777 | IPC_CREAT);
    if (queueId < 0)
    {
      // queue is yet present or error
      queueId = msgget(queueKey, 0777 | IPC_EXCL);
      if (queueId < 0)
      {
        // error
        printf("msgget (push) error\n");
      }
    }
    int s = msgsnd(queueId, (void *)&snd, sizeof(snd.mtext), IPC_NOWAIT);
    if (s < 0)
    {
      printf("push error\n");
    }
  }
  else if (strcmp(action, "pull") == 0)
  {
    long msgtyp = 0;
    queueId = msgget(queueKey, 0777 | IPC_EXCL);
    if (queueId < 0)
    {
      printf("msgget (pull) error\n");
      exit(6);
    }
    int r = msgrcv(queueId, (void *)&rcv, sizeof(rcv.mtext), msgtyp, MSG_NOERROR | IPC_NOWAIT);
    if (r < 0)
    {
      printf("pull error or empty queue\n");
      exit(7);
    }
    printf("Receiced %s\n", rcv.mtext);
  }
  else if (strcmp(action, "info") == 0)
  {
    queueId = msgget(queueKey, 0777 | IPC_EXCL);
    if (queueId < 0)
    {
      printf("msgget (info) error\n");
      exit(6);
    }
    msqid_ds mod;
    int i = msgctl(queueId, IPC_STAT, &mod);
    if (i < 0)
    {
      printf("msgctl info error\n");
      exit(7);
    }
    printf("Queue %d has %d message(s)\n", queueId, (int)mod.msg_qnum);
  }
  else
  {
    exit(5);
  }

  return 0;
}
