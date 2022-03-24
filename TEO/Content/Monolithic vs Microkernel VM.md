Monolithic vs Microkernel VM
Hypevisor di tipo 1 possono usare approccio monolitico o microkernel
- **slide 18**
- con microkernel hypervisor solo con quello che è necessario e duplico nelle vms driver che devono essere usati, parte di virtualizzazione fatta da vm di gestione e non da hypervisor. ambienti piu isolati
- con monolitico hypervisor piu grosso, hypervisor fa virtualizzazione in stack, driver sono in hypervisors e sono condivisi ..