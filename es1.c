// Dati due eseguibili come argomenti del tipo ls e wc si eseguono in due processi distinti: il primo deve generare uno stdout redirezionato su un file temporaneo, mentre il secondo deve essere lanciato solo quando il primo ha finito leggendo lo stesso file come stdin.

// Ad esempio ./main ls wc deve avere lo stesso effetto di ls | wc.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  char *params[2];
  int fd = open("temp.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  int f = fork();
  if (f == 0)
  {
    // child
    
    params[0] = argv[1];
    params[1] = NULL;
    dup2(fd, 1); // stdout
    execvp(params[0], params);
  }
  else
  {
    // father
    wait(NULL);  // wait ONE child
    
    params[0] = argv[2];
    params[1] = NULL;
    dup2(fd, 0); // stdinput
    //riposizionare il file all'inizio : sposto offset a 0
    lseek(fd, 0, SEEK_SET); //Reset I/O pnt
    execvp(params[0], params);
  }

  return 0;
}