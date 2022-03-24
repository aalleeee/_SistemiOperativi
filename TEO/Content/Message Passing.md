Message Passing
**Scambio di Messaggi– i processi comunicano tra loro senza condividere variabili**
- proc A deve comunicare con B:
	- A mette messaggio con info e spedisce al kernel
	- kernel vede che è destinato a B e lo inoltra
- quindi sono due messaggi
- intermediazione del kernel
	- costosa
	- commutazione di mode (2) 
- stesso schema al contrario per da B a A
- proc A non puo spedire direttamente a B per ragioni di sicurezza
	- kernel controlla che A possa comunicare con B
		- ex B non ha richiesto nulla
	- sicurezza che A e B non possono comunicare se la cosa non è autorizzata
		- kerenl supevisiona