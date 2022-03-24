# Processi e Thread
🔗 https://didatticaonline.unitn.it/dol/pluginfile.php/1578294/mod_resource/content/1/05-Processi%20e%20Threadslong.pdf

[[Indice 4 Processi e Threads]]

---

`11/03/2022`

![[Concetto di processo]]

![[Immagine in memoria]]

![[Stato di un processo]]

![[Scheduling]]

![[Code di scheduling]]

![[Operazione di dispatch]]


`17/03/2022`

![[Operazione sui processi]]

![[Creazione di un processo]]

![[Creazione processo in UNIX]]

![[Terminazione di un processo]]

![[Thread]]

![[Multi-threading]]

![[Vantaggi Multi-threading]]

**Esempi slide 32 - 33**
- nota che non necessariamente in slide 33 si dopo che primo thread va in time-limit si esegue l'altro, tutti e due sono di nuovo di fase di pronto e viene estratto un altro (che potrebbe essere di nuovo il primo)

![[Stati di un thread]]

![[Implementazione di thread]]

![[Vantaggi e svantaggi User-level thread]]

`18/03/22`

![[Vantaggie e svantaggi Kernel-level thread]]

![[LIBRERIA POSIX PTHREADS]]

![[Esempio threads con posix]]


Sincronizzazione tra thread
- strumenti avanzati per sincronizzazione tra molti thread
	- problemi di consistenza quando c'è condivisone di risorse
- ex i semafori


RELAZIONE TRA PROCESSI

![[Relazione tra processi]]

![[Modelli di comunicazione processi cooperanti]]

![[Message Passing]]

![[Meccanismi per Message Passing]]

![[Nominazione Message Passing]]
	
![[Comunicazione diretta Message Passing]]

![[Comunicazione indiretta Message Passing]]

![[Sincronizzazione Message Passing]]

![[Memoria condivisa]]

![[Memoria condivisa in Posix]]

![[Pipe]]

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