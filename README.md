# MC504syscalls
MC504 - Sistemas Operacionais - Igor Gustavo Hitzschky - Julianny Favinha - João Vítor Buscatto Silva - Ronaldo Prata Amorim - SYSTEM CALLS PROJECT

Using linux-4.8.8

Using config-4.8.6

## Install QEMU

$ sudo apt-get install qemu-system-x86


## IMPORTANT FILES

### Syscalls's table

MC504syscalls/linux-4.8.8/arch/x86/entry/syscalls/syscall_32.tbl

### Declaration of the functions

MC504syscalls/linux-4.8.8/include/linux/syscalls.h

### (380) settmpkey's function

MC504syscalls/linux-4.8.8/arch/x86/kernel/setgetkey.c

### (381) gettmpkey's function

MC504syscalls/linux-4.8.8/arch/x86/kernel/getgetkey.c

### Makefile

MC504syscalls/linux-4.8.8/arch/x86/kernel/Makefile

### Main function

MC504syscalls/ex-setgettmpkey.c
