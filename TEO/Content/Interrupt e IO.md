Interrupt e I/O
1. CPU driver dice cosa deve fare a il dispositivo
2. contemporanemente fa altre operazioni
3. con interrupt dispositivo segnala fine elaborazione a cpu
4. cpu riceve segnale di interrupt
	- interrompre salvando lo stato
	- salta in locazione definita
	- trasferisce dati
	- riprende instruzione interrota

problema
- con grandi quantità di dati i/o interrupt non è efficiente perché cpu interrotta continuamente
- soluzione è [[DMA]] (Direct Memory Access)