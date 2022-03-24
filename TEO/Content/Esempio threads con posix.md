Esempio threads con posix
**da slide 49 !!!**
- tbody flusso di esec del thread: codice che deve eseguire il thread
- il main è esso stesso un thread: crea un flusso senza doverlo specificare
- con **thread facile per padre ottenere figlio** : condividono stesso spazio di dati
	- fare l'esempio con processi non funziona: con wait non ho valore di ritorno del figlio da passare al padre
- **con fork processi i due spazi di indirizzamento sono disgiunti** (non condiviso)
- **con i thread è diverso: lo spazio di indirizzamento è condiviso**
	- thread condivide con processo tutto tranne suo stack locale e pcb/tcb