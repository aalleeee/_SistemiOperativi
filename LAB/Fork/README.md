https://didatticaonline.unitn.it/dol/pluginfile.php/1585610/mod_resource/content/1/Labso2022-Lesson_04b.pdf

---

# Shell e file
## Permessi
- `chown(path, id owner, id gruppo)`
- `fchown(int id file, id owner, id gruppo)`
	- ex int fd = open("file",O_RDONLY);
	- fchown(fd, 0, 0); // Change owner to root:root
- `chmod(path, mode)`
	- ex chmod("file",S_IRUSR|S_IRGRP|S_IROTH); // Permission to r/r/r
- `fchmod(int id file, mode)`

## Eseguire programmi: exec_()
- `execv(path, argv[])`
- `execvp(file, argv[])`
- `execle(file, par1, par2, ... , NULL, env)`

Esempi da slide 4

## Chiamare la shell
- `int system(const char * string)`
	- ex: int outcome = system("echo ciao"); // execute command in shell


# Forking
- generazione di nuovi processi (uno alla volta) partendo da uno esistente
- processo attivo invoca la syscall e così il kernel lo “clona"
	- clonati elementi principali
		- PC
		- registri
		- tabella dei file
		- variabili
	- alcune informazioni e in particolare quelle che riguardano la sua collocazione nella gerarchia complessiva dei processi sono modificate
		- pid e ppid aggiornati
- processo che effettua la chiamata è definito “padre”, quello generato è definito “figlio”

```C
f=fork();
printf(“\n”);   // istruzione ripetuta da processo clonato
```
- il valore è -1 in caso di errore
- se ha successo entrambi i processi:
	- processo padre riceve come valore il nuovo PID del processo figlio
	- processo figlio riceve come valore 0

## Identificativi dei processi
- PID - Process ID
	- `pid_t getpid()` : restituisce il PID del processo attivo
- PPID - Parent Process ID
	- `pid_t getppid()` : restituisce il PID del processo padre
- ...
	- SID - Session ID
	- EUID - Effective User ID

Esempio:

```C
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
  printf("$$ = ");
  fflush(stdout);
  system("echo $$"); // subshell
  printf(" PID: %d PPID: %d\n", getpid(), getppid());
  return 0;
}
```
- getppid() mi torna l'id della shell (che è il processo padre)
- la system torna l'id della subshell creata per il programma
- getpid() tona id del processo
	- notare che sono consecutivi
- fflush serve per forzare ad aspettare la fine dell'output prima di eseguire le istruzioni successive


## Wait
- `pid_t wait (int *status)` : attende la conclusione di UN figlio e ne restituisce il PID riportando lo status
- `pid_t waitpid(pid_t pid, int *status, int options)` : analoga a wait ma con opzioni e si specifica pid:
	- -n (<-1: attende un qualunque figlio il cui “gruppo” è |-n|)
	- -1 (attende un figlio qualunque)
	- 0 (attende un figlio con lo stesso “gruppo” del padre)
	- n (n>0: attende il figlio il cui pid è esattamente n)
- note
	- wait(st) corrisponde a waitpid(-1, st, 0)
	- while(wait(NULL)>0); attende tutti i figli

Interpretazione di stato ...

## Esempio fork multiple
```C
#include <stdio.h> 
#include <unistd.h>
int main()
{
  fork();
  fork();
  fork();
  printf("hello\n");
  return 0;
} 
  
```

stampa 8 volte hello
- spiegazione:
	- F F F print
		1. F F print
			1. F print
				1. print 1
				2. print 2
			2. F print
				1. print 3
				2. print 4 
		2. F F print
			1. F print
				1. print 5
				2. print 6
			2. F print
				1. print 7
				2. print 8


## Esempio Fork & Wait
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
int main()
{
  int wid, st, r;
  int fid = fork();             // Generate child

  srand(time(NULL));            // Initialise random
  r = rand() % 256;             // Get random
  
  if (fid == 0)
  {
    // If it is child
    printf("Child... (%d)", r);
    fflush(stdout);
    sleep(3);                   // Pause execution for 3 seconds
    printf(" done!\n");
    exit(r);                    // Terminate with random signal
  }
  else
  {
    // If it is parent
    printf("Parent...\n");
    wid = wait(&st);            // wait for ONE child to terminate
    printf("...child’s id: %d==%d (st=%d)\n", fid, wid, WEXITSTATUS(st));
  }
}
```

ex output
```sh
Parent...
Child... (165) done!
...child’s id: 1422==1422 (st=165)
```

```sh
Parent...
Child... (104) done!
...child’s id: 1420==1420 (st=104)
```


## Processi zombie e orfani
- quando un processo termina il suo stato di uscita è “catturato” dal padre
	- se il padre non cattura lo stato d’uscita i processi figli sono definiti “zombie”
	- se un padre termina prima del figlio, quest’ultimo è definito “orfano”
		- e viene “adottato” dal processo principale
- processo zombie che diventa anche orfano è poi gestito dal processo che lo adotta