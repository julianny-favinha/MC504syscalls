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
#include <linux/slab.h> // Biblioteca para kmalloc e kfree
#include <linux/jiffies.h> // Constantes jiffies e HZ

typedef struct node {
	char * value;
	int key; 
	unsigned int lifeT; // Total Lifespan
	unsigned int lifeS; // Inicio Lifespan
	struct node *next;
} Node, * ImplNode;

typedef struct hash {
	struct node *head;
} Hash, * ImplHash;

int eleCount = 0; // ? Pode ser qualquer número, pessoalmente colocaria 20
ImplHash hashTable = NULL; // (ImplHash) kmalloc(sizeof(elecount * Hash))
//TODO: Persistência?

ImplNode createNode(int key, char *value, int lifespan){
	ImplNode newNode;

	newNode = (ImplNode) kmalloc(sizeof(Node));
	newNode->key = key;
	strcpy(newNode->value, value);
	newNode->lifeT = lifespan;
	newNode->lifeS = jiffies/HZ;
	newNode->next = NULL;
	return newNode;
}

// TODO: Quando será falso?
int insertToHash(int key, char *value, int lifespan){
	int hashIndex = key % eleCount;
	ImplNode newNode = createNode(key, value, lifespan);

	if(!hashTable[hashIndex].head) {
		hashTable[hashIndex].head = newNode;
		return 0; // Inseriu 
	}

	newNode->next = (hashTable[Index].head)
	hashTable[index].head = newNode;
	return 0; // Inseriu 
}

int deleteFromHash(int key){
	int hashIndex = key % eleCount;
	ImplNode aux, myNode = hashTable[hashIndex].head;

	if(!myNode){
		return -1; // Não existe
	}

	aux = myNode;
	while(myNode != NULL){
		if(myNode->key == key){
			if(myNode == hashTable[hashIndex].head)
				hashTable[hashIndex].head = myNode.next;
			else
				aux->next = myNode->next;
			
			kfree(myNode);
			return 0; // Removeu 
		}
		aux = myNode;
		myNode = myNode->next;
	}

	return -1; // Não existe
}

char * getValue(int key){
	int hashIndex = key % eleCount;
	ImplNode myNode = hashTable[hashIndex].head;
	char * value = NULL

	if(!myNode){
		return value; // Não existe
	}

	while(myNode != NULL){
		if(myNode->key == key) {
			if(jiffies/HZ - myNode->lifeS >= myNode->lifeT)
				deleteFromHash(myNode->key); // Tempo esgotado
			else 
				value = myNode->value; // Existe
			return value;
		}
		myNode = myNode->next;
	}

	return value; // Não existe
}

asmlinkage long sys_settmpkey(int key, char* value, unsigned int lifespan){
	char * valueK;

	strncpy_from_user(valueK, value, strnlen_user( value, 10));
	return insertToHash(key, valueK, lifespan);
}

asmlinkage long sys_gettmpkey(int key, int n, char* value){
	char * valueK = getValue(key);
	if (!valueK)
		return -1;
	copy_to_user(value, valueK, n);
	return 0;
}

//TODO: testar funções no mesmo arquivo
//TODO: remover bugs