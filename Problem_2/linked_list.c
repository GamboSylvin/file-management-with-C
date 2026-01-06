#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

Node* appendNode(List* list, int data) {
	if (!list) return NULL;
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) {
		return NULL;
	}
	newNode->data = data;
	newNode->next = NULL;
	if (!list->tail) {
		list->head = newNode;
		list->tail = newNode;
	}
	else {
		list->tail->next = newNode;
		list->tail = newNode;
	}
	return newNode;
}