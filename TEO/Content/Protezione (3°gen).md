**Importante ora la sicurezza** 
- stabilire qual è l'utente che si collega e se/che accessi ha
- protezione da errori (ex cilco infinito) che potrebbero danneggiare macchina o utente, indipendentemente dal programma
- introdotti meccanismi di protezione
	- I/O (programma che danneggia hd)
	- memoria (programma che legge o scrive dati di un altro utente)
	- cpu (macchina sempre sotto controllo so)

**Protezione I/O**
- implementando **dual mode**: so deve differenziare se programma gira in modalità
	- utente: operazioni limitate, operaz io possono essere invocate ma non eseguire
		- si commuta in mod kernel ed è il so che accede a risorse i/o
	- supervisor (kernel): so accede a risorse i/o

**Protezione memora**
- protezione di spazio dei vari processi
- protezione del monitor
- associo a registri limite a ogni processo

**Protezione cpu**
- so deve mantenere controllo sistema
- realizzata con timer
	- associato a ogni job
	- a scadenza, controllo torna a monitor