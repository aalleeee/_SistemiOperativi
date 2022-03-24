Creazione di un processo

- processo puo creare processo figlio
	- figlio ottiene risorse da so o da padre
	- creazione di processi può cambiare in base a so
		- ex divisione o condivisione risorse con il processo figlio
- creazione
	- **sincrona**
		- creo figlio e padre aspetta che figlio termina per riprendere sua esecuzione
	- **asincrona**
		- creo figlio e sono in concorrenza di padre e figli
		- entrambi in coda proc pronti