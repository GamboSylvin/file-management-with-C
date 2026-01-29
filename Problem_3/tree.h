#ifndef TREE_H
#define TREE_H
#include <string.h>
#include<stdio.h>

typedef struct Node {
	char name[20];
	char phoneNumber[15];
	int height;
	struct Node* left;
	struct Node* right;
} Node;

Node* createDB(FILE* file);
void destroyDB(Node* root);
Node* insertNode(Node* root, const char* name, const char* number);
Node* deleteNode(Node* root, Node* nodeToDelete);
Node* findNode(Node* root, const char* name);
void readDB(Node* root);
int setHeight(Node* root);
int getBf(Node* root);
Node* rotateLeft(Node* root);
Node* rotateRight(Node* root);
Node* findSuccessor(Node* root);

#endif
