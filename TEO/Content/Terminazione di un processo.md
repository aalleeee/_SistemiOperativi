Terminazione di un processo
opzioni:
- processo termina esecuzione
- processo terminato da padre
	- ex per troppo uso di risorse
	- se figlio non è più necessario
	- padre termina e uccide figli
		- **se padre muore e figlio non ucciso, nessuno può ucciderlo**
		- se padre muore di solito uccide anche figli
			- altrimenti questi diventano zombie
			- overhead
- modo corretto di terminare figlio e terminazione dal padre e quindi libera risorse
	- solo padre puo rimuovere pcb del figlio
	- altrimenti deve farlo il so con specifiche
- processo terminato da so
	- errori
	- utente termina processi