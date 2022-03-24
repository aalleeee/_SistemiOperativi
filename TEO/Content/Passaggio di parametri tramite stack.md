Passaggio di parametri tramite stack
- **da slide 31**
- gestito in mod LIFO
	- istruzioni push e pop
- passaggi:
	1. carico parametri su stach
		- push dei parametri in ordine inverso
	2. chiamo la funzione
	3. carico numero della system call in registro specifico
	4. invoco una TRAP (interrupt)
		- fermo prog utente
		- subentra kernel
		- passo da USER MODE a KERNEL MODE
		- salto a codice del dispacher 
	5. tramite tabella arrivo a implementazione e eseguo funzione
	6. ritorno a funzione di lib
		- ritorno in USER MODE
		- carico program counter PC
	7. incremento stack pointer SP per rimuovere param della chiamata
		- la cancellazione avviene spostando SP e non cancellando i dati
		- poi li sovrascrivo
		- so non perde tempo per cancellare dati
		- **quindi** i dati non sono mai cancellati