#include <linux/slab.h> // Biblioteca para kmalloc e kfree
#include <linux/jiffies.h> // Constantes jiffies e HZ
#include "hashtable.h"

int eleCount = 20; 
ImplHash hashTable = NULL;

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