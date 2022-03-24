Sovrapposizione di CPU e I/O
- prossimo step è sovrappore op I/O e CPU su stessa macchina.
- per fare questo mi serve hd: serve l' **interrupt** hardware :
	- ad ex CPU deve sapere quando operazione I/O finisce, l'unica soluz senza interrupt potrebbe essere con continue interrogazioni ai dispositivi
- serve un meccaniscmo asicrono che fa richieste a IO non bloccanti
- la sovrapposizione puo essere fatta solo se la semanitca del programma lo consente
- se il prog è bloccante (dati mi servono per andare avanti) allora non si puo fare
- altra alternativa è DMA (direct memory access)