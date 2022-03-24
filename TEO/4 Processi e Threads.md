# Processi e Thread
🔗 https://didatticaonline.unitn.it/dol/pluginfile.php/1578294/mod_resource/content/1/05-Processi%20e%20Threadslong.pdf

[Indice 4 Processi e Threads](Indice%204%20Processi%20e%20Threads.md)

---

`11/03/2022`

![Concetto di processo](Concetto%20di%20processo.md)

![Immagine in memoria](Immagine%20in%20memoria.md)

![Stato di un processo](Stato%20di%20un%20processo.md)

![Scheduling](Scheduling.md)

![Code di scheduling](Code%20di%20scheduling.md)

![Operazione di dispatch](Operazione%20di%20dispatch.md)


`17/03/2022`

![Operazione sui processi](Operazione%20sui%20processi.md)

![Creazione di un processo](Creazione%20di%20un%20processo.md)

![Creazione processo in UNIX](Creazione%20processo%20in%20UNIX.md)

![Terminazione di un processo](Terminazione%20di%20un%20processo.md)

![Thread](Thread.md)

![Multi-threading](Multi-threading.md)

![Vantaggi Multi-threading](Vantaggi%20Multi-threading.md)

**Esempi slide 32 - 33**
- nota che non necessariamente in slide 33 si dopo che primo thread va in time-limit si esegue l'altro, tutti e due sono di nuovo di fase di pronto e viene estratto un altro (che potrebbe essere di nuovo il primo)

![Stati di un thread](Stati%20di%20un%20thread.md)

![Implementazione di thread](Implementazione%20di%20thread.md)

![Vantaggi e svantaggi User-level thread](Vantaggi%20e%20svantaggi%20User-level%20thread.md)

`18/03/22`

![Vantaggie e svantaggi Kernel-level thread](Vantaggie%20e%20svantaggi%20Kernel-level%20thread.md)

![LIBRERIA POSIX PTHREADS](LIBRERIA%20POSIX%20PTHREADS.md)

![Esempio threads con posix](Esempio%20threads%20con%20posix.md)


Sincronizzazione tra thread
- strumenti avanzati per sincronizzazione tra molti thread
	- problemi di consistenza quando c'è condivisone di risorse
- ex i semafori


RELAZIONE TRA PROCESSI

![Relazione tra processi](Relazione%20tra%20processi.md)

![Modelli di comunicazione processi cooperanti](Modelli%20di%20comunicazione%20processi%20cooperanti.md)

![Message Passing](Message%20Passing.md)

![Meccanismi per Message Passing](Meccanismi%20per%20Message%20Passing.md)

![Nominazione Message Passing](Nominazione%20Message%20Passing.md)
	
![Comunicazione diretta Message Passing](Comunicazione%20diretta%20Message%20Passing.md)

![Comunicazione indiretta Message Passing](Comunicazione%20indiretta%20Message%20Passing.md)

![Sincronizzazione Message Passing](Sincronizzazione%20Message%20Passing.md)

![Memoria condivisa](Memoria%20condivisa.md)

![Memoria condivisa in Posix](Memoria%20condivisa%20in%20Posix.md)

![Pipe](Pipe.md)

esempi di codice
...
...

`24/03/22`

esempi di codice
...
...


f_to_key() -> ftok()



con pipe con nome viene creato riferimento nel filesystem che appare come file ma è una pipe, è una referenza nel filesystem

---

Processi di sistema operativo

- processi del so sono processi a tutti gli effetti

processi del kernel
3 soluzioni
- kernel non implementati come proc
	- so spazio di memoria riservato
	- ...
	- eseguito separatamente
	- tutto quello che è kernel implementato diverso
	- concetto di processo solo a proc utenti
	- non piu usato
		- due paradigmi di interazione (proc normali e kernel)
- kernel implementato all'interno di proc utente
	- se processo utente ha bisogno di funz kernel, queste vengono attaccate a questo processo
	- modifica spazio di indirizzi
		- si aggiunge "kernel stack"
		- si aggiunge "spazio di ind condiviso"
		- queste sono riservati a moduli del kernel che quel proc necessita
		- ...
		- ci sono comunque processi di kernel che devono sempre stare in memoria
			- ex scheduler o dispatcher
			- process switching functions
		- problema
			- spreco di memoria
				- moduli duplicati
				- kernel duplicato
		- vantaggio
			- context switch
			- ma no mode switch: dati kernel è gia nell'immagine
				- PCB è lo stesso
- kernel implementato come processo
	- piu moderno, piu usato
	- kernel e proc utenti trattati allo stesso modo
	- eccezioni per dispatcher e scheduler
		- non possono essere a loro volta processi
	- design e mantenimento semplice
	- proc kernel sono cmq diverso
		- necessarie priorità
		- 