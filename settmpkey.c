/* SYSTEM CALLS
 * 
 * Igor Gustavo Hitzschky Lema - 155758
 * João Vítor Buscatto Silva - 155951
 * Julianny Favinha Donda - 156059
 * Ronaldo Prata Amorim - 157228
 * 
 * 2º SEMESTRE DE 2016 - MC504 - Profa. Islene Calciolari Garcia
 * 
 * Chamadas de sistema que armazenam e recuperam pares de chave/valor 
 * com tempo de vida determinado no momento da criação.
 *
 * A função sys_settmpkey armazena a chave key no espaço de kernel.
 * Retorna 0 se a operação foi bem sucedida e -1 caso contrário.
 */ 

#include <linux/unistd.h>
#include <linux/linkage.h>
#include <linux/slab.h> // Biblioteca para kmalloc e kfree
#include <linux/uaccess.h> // Biblioteca para strncpy_from_user
#include "hashtable.h"

asmlinkage long sys_settmpkey(int key, char *value, unsigned int lifespan) {
	char *valueK = NULL;
	
	/* void * kmalloc(size_t size, int flags);
	 * flag GFP_KERNEL: This is a normal allocation and might block. This is 
	 * the flag to use in process context code when it is safe to sleep. 
	 * The kernel will do whatever it has to in order to obtain the memory 
	 * requested by the caller. This flag should be your first choice. */
	if (!hashTable)
		hashTable = (ImplHash) kmalloc(20 * sizeof(ImplHash),  GFP_KERNEL);
	
	/* strncpy_from_user retorna zero em caso de sucesso, diferente de 
	 * zero em caso de falha */
	if (!strncpy_from_user(valueK, value, strnlen_user(value, 10)))
		return insertToHash(key, valueK, lifespan);
		
	return -1;
}
