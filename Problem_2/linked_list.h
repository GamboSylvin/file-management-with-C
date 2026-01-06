#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node
{
	int data;
	struct Node* next;
} Node;

typedef struct List
{
	Node* head;
	Node* tail;
} List;

Node* appendNode(List* list, int data);

#endif
