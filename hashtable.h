/* SYSTEM CALLS
 * 
 * Igor Gustavo Hitzschky Lema - 155758
 * João Vítor Buscatto Silva - 155951
 * Julianny Favinha Donda - 156059
 * Ronaldo Prata Amorim - 157228
 * 
 * 2º SEMESTRE DE 2016 - MC504 - Profa. Islene Calciolari Garcia
 * */

#ifndef HASHTABLE_H_   
#define HASHTABLE_H_

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

extern ImplHash hashTable;

int insertToHash(int key, char *value, int lifespan);
int deleteFromHash(int key);
char *getValue(int key);

#endif 