Operazione di dispatch
1. **cambio di contesto**
	- salvataggio di [[Immagine in memoria#^2dd40b|PCB]] del processo che esce e carico quello del processo che entra
	- procedimento piu lento
	- passaggio da cpu a nuovo processo
		- registra stato del vecchio e carica stato del nuovo
		- slide 19
1. **passaggio a modalità utente**
	- a inizio di fare di dipatch siamo in mod kernel
2. **salto a istruzione da eseguire** del proc appena arrivato in cpu