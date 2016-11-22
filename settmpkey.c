/* 
 * SYSTEM CALLS
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
#include <linux/slab.h> // biblioteca para kmalloc e kfree
#include <linux/jiffies.h> // constantes jiffies e HZ

asmlinkage long sys_settmpkey(int key, char* value, unsigned int lifespan) {
	return -1;
}
