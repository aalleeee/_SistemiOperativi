# Segnali
https://didatticaonline.unitn.it/dol/pluginfile.php/1588047/mod_resource/content/1/Labso2022-Lesson_05.pdf

## Segnali
- possono avvenire vari eventi asincorni rispetto a normale flusso di un programma
	- ex richiesta di terminazione o di sospensione da parte di un utente, la terminazione di un processo figlio o un errore generico, ..
- Unix prevede la gestione di questi eventi attraverso i segnali
	- quando il sistema operativo si accorge di un certo evento, genera un segnale da mandare al processo interessato
	- che decide cosa fare
- con linux 32 segnali
	- per ognuno
		- valore numerico
		- etichetta SIG...
			- `SIGQUIT` (terminal quit)
			- `SIGCHLD` (child terminated)
			- `SIGINT` (terminal interrupt, CTRL + C)
			- `SIGKILL` (kill process)
			- ....

## Pending e Blocked signal
- per ogni processo due liste
	- pending signals: segnali emessi che il processo dovrà gestire
	- blocked signals: segnali non comunicati al processo
- processo reagisce in modo adeguato

## Gestione dei segnali
- segnali: software interrupts
	- interruzioni del normale flusso del processo generate dal sistema operativo
- il programma può decidere **come gestire l’arrivo di un segnale**
	- azione di default
	- ignorando (programma continua)
	- handler personalizzato (programma si interrompe)

## Default Handler
- ogni processo ne ha uno che può:
	- ignorare signal
	- terminare processo
	- continuare esecuzione
	- stoppare processo

Ogni processo può sostituire il gestore di default con una funzione “custom" e comportarsi di conseguenza
**La sostituzione avviene tramite la system call signal()** (definita in “signal.h”)

## signal()
- `signal(SIGINT,SIG_IGN);` : ignore signal
- `signal(SIGCHLD,SIG_DFL);` : use default handler
- `signal(SIGTSTP,myHandler);` : use myHandler

nel terzo caso serve:
`void myHandler(int sigNum){ ... }`



Esempio base 
```C
#include <signal.h> 
#include <stdio.h>
#include <stdlib.h>

void myHandler(int sigNum)
{
  printf("CTRL+Z\n");
  exit(2);
}

int main(void)
{
  signal(SIGTSTP, myHandler);
  while (1);
}

// if you press CTRL+Z (terminal stop) singal calls cutom handler that prints "CTRL+Z"
```

## Custom handler
- deve essere una funzione di tipo void che accetta come argomento un intero, il quale rappresenta il segnale catturato
	- consente l’utilizzo di un solo handler per segnali differenti.

Esempio:

```C
#include <signal.h>  #include <stdio.h> #include <stdlib.h>

void myHandler(int sigNum)
{
  if (sigNum == SIGINT)
    printf("CTRL+C\n");
  else if (sigNum == SIGTSTP)
    printf("CTRL+Z\n");
  exit(2);
}

int main(int argc, char const *argv[])
{
  signal(SIGINT, myHandler);
  signal(SIGTSTP, myHandler);
  while (1);
  return 0;
}

/* one custom handler 2 singal
if you press CTRL+Z (terminal stop) singal calls custom handler that prints "CTRL+Z"
if you press CTRL+C (terminal interrupt) singal calls custom handler that prints "CTRL+C" */
```

## signal() return
- signal() **restituisce un riferimento all’handler che era precedentemente assegnato al segnale**

	- `NULL` : handler precedente era l’handler di default
	- `1` : l’handler precedente era SIG_IGN
	- `address`: l’handler precedente era * (address)

Esempio
```C
#include <signal.h>
#include <stdio.h>

void myHandler(int sigNum) {}

int main()
{
  printf("DFL: %p\n", signal(SIGINT, SIG_IGN));
  printf("IGN: %p\n", signal(SIGINT, myHandler));
  printf("Custom: %p == %p\n", signal(SIGINT, SIG_DFL), myHandler);
}

// first singal return NULL : previous handler was a default one
// second signal return 1 : previous handler was SIG_IGN : signal(SIGINT, -> SIG_IGN)
// third signal return 0x55850ef45169 : previous handler was myHandler : printf("IGN: %p\n", signal(SIGINT, -> myHandler));
//    0x55850ef45169 == 0x55850ef45169
```


## Inviare i segnali: kill()
`int kill(pid_t pid, int sig);`

- **invia un segnale** ad uno o più processi a seconda dell’argomento pid
	- pid > 0: segnale al processo con PID=pid
	- pid = 0: segnale ad ogni processo dello stesso gruppo di chi esegue “kill”
	- pid = -1: segnale ad ogni processo possibile (stesso UID/RUID)
	- pid < -1: segnale ad ogni processo del gruppo |pid|
- restituisce 0 se il segnale viene inviato, -1 in caso di errore

Esempio
```C
//Basic example of kill() to send signal

#include <signal.h> #include <stdio.h> #include <stdlib.h> #include <sys/wait.h> #include <unistd.h>

void myHandler(int sigNum)
{
  printf("[%d]ALARM!\n", getpid());
}

int main(void)
{
  signal(SIGALRM, myHandler);

  int child = fork();
  if (!child)
    while (1); // block the child
  
  printf("[%d]sending alarm to %d in 3 s\n", getpid(), child);
  sleep(3);
  kill(child, SIGALRM); // send ALARM, child’s handler reacts

  printf("[%d]sending SIGTERM to %d in 3 s\n", getpid(), child);
  sleep(3);
  kill(child, SIGTERM); // send TERM: default is to terminate

  while (wait(NULL) > 0);
}

// output:
// [7374]sending alarm to 7375 in 3 s     -> kill 1 from child with SIGALRM that recall myHandler (*)
// [7374]sending SIGTERM to 7375 in 3 s   -> kill 2 from child 
// [7375]ALARM!                           -> (*) handler call from father after child terminate
```


## Kill da bash
- kill è anche un programma in bash che accetta come primo argomento il tipo di segnale (kill -l per la lista) e come secondo argomento il PID del processo
- ex  `$ kill -14`

## Programmare un alarm: alarm()
`unsigned int alarm(unsigned int seconds);`

...

## Mettere in pausa: pause()
`int pause();`

...

## Bloccare i segnali
- esiste anche la lista dei “blocked signals”
	- segnali ricevuti dal processo ma volutamente non gestiti
- i segnali ignorati non saranno mai gestiti
- **i segnali bloccati sono solo temporaneamente non gestiti**
	- rimane nello stato pending fino a quando esso non viene gestito oppure il suo handler tramutato in ignore
- l’insieme dei segnali che vanno bloccati è detto “signal mask”
	- maschera dei segnali che è modificabile attraverso la system call `sigprocmask()`

### sigset_t
- una signal mask può essere gestita con un `sigset_t`
	- lista di segnali modificabile con alcune funzioni
- queste funzioni modificano il sigset_t, non la maschera dei segnali del processo!
- funzioni
	- `int sigemptyset(sigset_t *set);` Svuota
	- `int sigfillset(sigset_t *set);` Riempie
	- `int sigaddset(sigset_t *set, int signo);` Aggiunge singolo
	- `int sigdelset(sigset_t *set, int signo);` Rimuove singolo
	- `int sigismember(const sigset_t *set, int signo);` Interpella

### sigprocmask()
`int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset);`

- a seconda del valore di how e di set, la maschera dei segnali del processo viene cambiata
	- how = SIG_BLOCK: i segnali in set sono aggiunti alla maschera;
	- how = SIG_UNBLOCK: i segnali in set sono rimossi dalla maschera;
	- how = SIG_SETMASK: set diventa la maschera.
- se oldset non è nullo, in esso verrà salvata la vecchia maschera (anche se set è nullo).