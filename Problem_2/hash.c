#include <stdio.h>
#include <stdlib.h>
#include "hash.h"



int insertToHash(List* hashTable, int data) {
	int index = hash((uint32_t)data);
	if(appendNode(hashTable+index, data))
		return 0;
	return -1;
}

uint32_t hash(uint32_t key) {
	const int c = 2654435761u;
	int index = (key*c) >> 22;
	return index;
}

int searchInHash(List* hashTable, int data){
	int index = hash((uint32_t)data);
	Node* current = hashTable[index].head;
	while(current){
		if (current->data == data)
			return index;
		current = current->next;
	}
	return -1;
}