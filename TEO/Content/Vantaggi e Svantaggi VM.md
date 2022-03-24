Vantaggi e Svantaggi VM
**vantaggi**:
- isolamento
- protezione
- piu os su stessa macchina
- ottimizzazione risorse
- sviluppo di so
	- sotto c'è quello principale
	- isolo un altro in sviluppo
- sviluppo prot di rete
	- simulazioni di reti
- portabilità

**svantaggi:** 
- prestazioni
- condivisione di hypervisor
	- impossibile con tipo 1
	- soluzioni
		- rete virtuale
		- si condivide espressamente file system o sua parte
- gestire dual mode virtuale
	- sistema gestione vm gira in kernel mode
	- vm esegue in user mode