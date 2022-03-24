Vantaggi e svantaggi User-level thread
- **vantaggi**
	- context swith efficiente: non devo passare in kernel mode per usare thread
	- scheduler configurabile in base a appl
	- portabilità
		- puo girare sia in multi che single thread
- **svantaggi**
	- blocco di un thread blocca intero processo
	- non posso sfruttare multiprocessore
		- scheduling di thread sempre su stesso proc -> un thread per ogni processo