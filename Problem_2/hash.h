#ifndef HASH_H
#define HASH_H
#include "linked_list.h"
#include <stdint.h>


int insertToHash(List* hashtable, int data);
uint32_t hash(uint32_t key);
int searchInHash(List* hashtable, int data);

#endif
