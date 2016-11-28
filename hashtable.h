#ifndef HASHTABLE_H_   
#define HASHTABLE_H_

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

extern ImplHash hashTable;

int insertToHash(int key, char *value, int lifespan);
int deleteFromHash(int key);
char * getValue(int key);

#endif 