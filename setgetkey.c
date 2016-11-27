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
 *
 * A função sys_gettmpkey copia em value o valor da chave key com no
 * máximo n caracteres.
 * Retorna 0 se encontrou chave válida e -1 caso contrário.
 */ 

#include <linux/unistd.h>
#include <linux/linkage.h>
#include <linux/slab.h> // kmalloc e kfree
#include <linux/jiffies.h> // Constantes jiffies e HZ
#include <linux/uaccess.h> // strncpy_from_user e copy_to_user

#define COUNT_ELEM_HASH 20 // qtd máxima de elementos na tabela hash **************************** PODE SER QUALQUER NUMERO!!! *********************

typedef struct node {
	char *value;
	int key; 
	unsigned int lifeT; // Total Lifespan
	unsigned int lifeS; // Inicio Lifespan
	struct node *next;
} Node, *ImplNode;

typedef struct hash {
	struct node *head;
} Hash, *ImplHash;

int eleCount = 0; // qtd atual de elementos na tabela hash
ImplHash hashTable = NULL; // (ImplHash) kmalloc(sizeof(elecount * Hash))
//TODO: Persistência?

ImplNode createNode(int key, char *value, int lifespan) {
	ImplNode newNode;

	newNode = (ImplNode) kmalloc(sizeof(Node), GFP_KERNEL); // TODO: NULL? void * kmalloc(size_t size, int flags)
	/* GFP_KERNEL: This is a normal allocation and might block. This is the flag to use in process context code when it is safe to sleep. The kernel will do whatever it has to in order to obtain the memory requested by the caller. This flag should be your first choice. */
	newNode->key = key;
	strcpy(newNode->value, value);
	newNode->lifeT = lifespan;
	newNode->lifeS = jiffies/HZ;
	newNode->next = NULL;
	return newNode;
}

// TODO: Quando será falso?  ------ R: Quando o hash nao estiver cheio, ou seja, nao ultrapassou COUNT_ELEM_HASH
// TODO: Em algum caso que não de pra inserir, é preciso olhar se o lifespan expirou?
int insertToHash(int key, char *value, int lifespan){
	int hashIndex = key % COUNT_ELEM_HASH;
	ImplNode newNode;
	
	// É possível inserir somente se a qtd de elementos atual não ultrapassou o limite
	if (eleCount < COUNT_ELEM_HASH) {
		newNode = createNode(key, value, lifespan);
		
		// Incrementa qtd atual de elementos da tabela hash
		eleCount++;
		
		if(!hashTable[hashIndex].head) {
			hashTable[hashIndex].head = newNode;
		}
		else {
			newNode->next = hashTable[hashIndex].head;
			hashTable[hashIndex].head = newNode;
		}
		return 0; // Inseriu 
	}

	// Não conseguiu inserir 
	return -1;
}

int deleteFromHash(int key) {
	int hashIndex = key % eleCount;
	ImplNode aux, myNode = hashTable[hashIndex].head;

	// É possível deletar somente se existir pelo menos um elemento
	if (eleCount > 0) {
		if (!myNode) {
			return -1; // Não existe
		}

		aux = myNode;
		while (myNode != NULL) {
			if (myNode->key == key) {
				if (myNode == hashTable[hashIndex].head) {
					hashTable[hashIndex].head = myNode->next;
				}
				else {
					aux->next = myNode->next;
				}
				
				kfree(myNode);
				
				// decrementa qtd atual de elementos da tabela hash
				eleCount--;
				return 0; // Removeu 
			}
			aux = myNode;
			myNode = myNode->next;
		}
	}

	return -1; // Não existe
}

char *getValue(int key) {
	int hashIndex = key % eleCount;
	ImplNode myNode = hashTable[hashIndex].head;
	char * value = NULL;

	if (!myNode) {
		return value; // Não existe
	}

	while (myNode != NULL) {
		if (myNode->key == key) {
			if (jiffies/HZ - myNode->lifeS >= myNode->lifeT)
				deleteFromHash(myNode->key); // Tempo esgotado
			else 
				value = myNode->value; // Existe
			return value;
		}
		myNode = myNode->next;
	}

	return value; // Não existe
}

asmlinkage long sys_settmpkey(int key, char* value, unsigned int lifespan) {
	char *valueK = NULL;

	// strncpy_from_user retorna zero em caso de sucesso, diferente de zero em caso de falha
	if (!strncpy_from_user(valueK, value, strnlen_user(value, 10)))
		return insertToHash(key, valueK, lifespan);
		
	return -1;
}

asmlinkage long sys_gettmpkey(int key, int n, char* value) {
	char * valueK = getValue(key);
	
	if (!valueK)
		return -1;
	
	// copy_to_user retorna zero em caso de sucesso, ou diferente de zero para indicar o número de bytes que não foram transferidos	
	if (!copy_to_user(value, valueK, n))
		return -1;
		
	return 0;
}

//TODO: testar funções no mesmo arquivo
//TODO: remover bugs
