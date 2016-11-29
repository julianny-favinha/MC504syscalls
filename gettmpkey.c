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
 * A função sys_gettmpkey copia em value o valor da chave key com no
 * máximo n caracteres.
 * Retorna 0 se encontrou chave válida e -1 caso contrário.
 */ 

#include <linux/unistd.h>
#include <linux/linkage.h>
#include <linux/uaccess.h> // Biblioteca para copy_to_user
#include "hashtable.h"
 
asmlinkage long sys_gettmpkey(int key, int n, char *value) {
	char *valueK = getValue(key);
	
	if (!valueK)
		return -1;
	
	/* copy_to_user retorna zero em caso de sucesso, ou diferente de 
	 * zero para indicar o número de bytes que não foram transferidos */		
	if (copy_to_user(value, valueK, n))
		return -1;
	
	return 0;
}

//TODO: testar funções no mesmo arquivo
//TODO: remover bugs
