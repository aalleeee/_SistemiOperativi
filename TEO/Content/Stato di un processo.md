Stato di un processo
- durante l'esec (da quando entra a quando esce in mem) un processo **evolve in vari stati**
- schema di base **slide 9**
	1. porto processo in memoria ma non è ancora in esecuzione (non ha cpu)
		- ce ne sono molti, ognuno ha sua immagine
	2. so ne sceglie uno : dispatch
	3. gli assegna la cpu
	4. ora 2 opzioni
		1. finisce
		2. esce da cpu
		- non è finito
			5. torno in ram ma non ho piu la cpu (stato di attesa prima e poi stato di essere pronto)

**alternanza di stato di pronto, dispatcher, avere cpu, tornare in ram senza cpu e di nuovo avere cpu** ... poi a una certa finisce
-> **slide 10**
c'è feature di prelazione o time out