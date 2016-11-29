/* SYSTEM CALLS
 * 
 * Igor Gustavo Hitzschky Lema - 155758
 * João Vítor Buscatto Silva - 155951
 * Julianny Favinha Donda - 156059
 * Ronaldo Prata Amorim - 157228
 * 
 * 2º SEMESTRE DE 2016 - MC504 - Profa. Islene Calciolari Garcia
 * */

#include <linux/slab.h> // Biblioteca para kmalloc e kfree
#include <linux/jiffies.h> // Constantes jiffies e HZ
#include "hashtable.h"

int eleCount = 20; // Número de chaves na Table
ImplHash hashTable = NULL;

// Cria novo nó para lista
ImplNode createNode(int key, char *value, int lifespan) {
	ImplNode newNode;

	newNode = (ImplNode) kmalloc(sizeof(Node), GFP_KERNEL);
	newNode->key = key;
	strcpy(newNode->value, value);
	newNode->lifeT = lifespan;
	newNode->lifeS = jiffies/HZ;
	newNode->next = NULL;
	return newNode;
}

// Insere na table na cabeça da lista
int insertToHash(int key, char *value, int lifespan) {
	int hashIndex = key % eleCount;
	ImplNode newNode = createNode(key, value, lifespan);

	if(!hashTable[hashIndex].head) {
		hashTable[hashIndex].head = newNode;
		return 0; // Inseriu 
	}

	newNode->next = (hashTable[hashIndex].head);
	hashTable[hashIndex].head = newNode;
	return 0; // Inseriu 
}

// Deleta o elemento da lista
int deleteFromHash(int key) {
	int hashIndex = key % eleCount;
	ImplNode aux, myNode = hashTable[hashIndex].head;

	if(!myNode) {
		return -1; // Não existe
	}

	aux = myNode;
	while(myNode != NULL) {
		if(myNode->key == key) {
			if(myNode == hashTable[hashIndex].head)
				hashTable[hashIndex].head = myNode->next;
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

// Busca o valor guardado de uma chave específica, se o tempo for esgotado deleta
char *getValue(int key){
	int hashIndex = key % eleCount;
	ImplNode myNode = hashTable[hashIndex].head;
	char *value = NULL;

	if(!myNode) {
		return value; // Não existe
	}

	while(myNode != NULL) {
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
