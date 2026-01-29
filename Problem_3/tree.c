#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Node* createDB(FILE* file) {
	if(!file) {
		fprintf(stderr, "Invalid file pointer passed to createDB.\n");
		return NULL;
	}
	char name[20];
	char number[15];
	int readValue = 1;
	Node* root = NULL;
	while (readValue) {
		readValue = fscanf(file, "%19s %14s", name, number);
		if (readValue == EOF) {
			if(feof(file)) {
				break; 
			}
			else if (ferror(file)) {
				perror("Error reading from file");
				return NULL;
			}
			else {
				fprintf(stderr, "file format error.\n");
				return NULL;
			}
		}
		root = insertNode(root, name, number);
		if(!root){
			fprintf(stderr,"Failed to insert the contact into the database.\n");
			return NULL;
		}
	}
	
	return root;
}

void destroyDB(Node* root) {
	if (!root) {
		return;
	}
	destroyDB(root->left);
	destroyDB(root->right);
	free(root);
}

Node* insertNode(Node* root, const char* name, const char* number) {
	if (!name || !number) {
		fprintf(stderr, "Invalid parameters passed to insertNode.\n");
		return NULL;
	}
	if (!root) {
		Node* newNode = (Node*)malloc(sizeof(Node));
		if(!newNode){
			perror("Memory allocation failed while inserting a new node.\n");
			return NULL;
		}
		strcpy(newNode->name, name);
		strcpy(newNode->phoneNumber, number);
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->height = setHeight(newNode);

		return newNode;
	}
	if (strcmp(name, root->name) < 0) {
		root->left = insertNode(root->left, name, number);
	} else if (strcmp(name, root->name) > 0) {
		root->right = insertNode(root->right, name, number);
	} else {
		fprintf(stderr, "Duplicate entry: A contact with the name '%s' already exists.\n", name);
		return root;
	}
	root->height = setHeight(root);
	int bf = getBf(root);
	int leftBf = getBf(root->left);
	int rightBf = getBf(root->right);

	if(bf >= 2){
		if(leftBf < 0){
			root->left = rotateLeft(root->left);
		}
		root = rotateRight(root);
	}
	else if(bf <= -2){
		if(rightBf > 0){
			root->right = rotateRight(root->right);
		}
		root = rotateLeft(root);
	}

	return root;
}

int setHeight(Node* root) {
	assert(root != NULL);
	int leftHeight = root->left ? root->left->height : -1;
	int rightHeight = root->right ? root->right->height : -1;
	return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int getBf(Node* root) {
	if(!root){
		return 0;
	}
	int leftHeight = root->left ? root->left->height : -1;
	int rightHeight = root->right ? root->right->height : -1;
	return leftHeight - rightHeight;
}

Node* deleteNode(Node* root, Node* nodeToDelete) {
	if (!root || !nodeToDelete) {
		fprintf(stderr, "Invalid parameters passed to deleteNode.\n");
		return NULL;
	}
	if (root == nodeToDelete) {
		if (!root->left && !root->right) {
			free(root);
			return NULL;
		}
		else if (!root->left) {
			Node* temp = root->right;
			free(root);
			return temp;
		}
		else if(!root->right){
			Node* temp = root->left;
			free(root);
			return temp;
		}
		else {
			Node* successor = findSuccessor(nodeToDelete);
			assert(successor != NULL);
			strcpy(root->name, successor->name);
			strcpy(root->phoneNumber, successor->phoneNumber);
			root->right = deleteNode(root->right, successor);
		}
	}
	else if (strcmp(nodeToDelete->name, root->name) < 0) {
		root->left = deleteNode(root->left, nodeToDelete);
	}
	else if(strcmp(nodeToDelete->name, root->name) > 0){
		root->right = deleteNode(root->right, nodeToDelete);
	}

	root->height = setHeight(root);
	int bf = getBf(root);
	int leftBf = getBf(root->left);
	int rightBf = getBf(root->right);

	if(bf >= 2){
		if(leftBf < 0){
			root->left = rotateLeft(root->left);
		}
		root = rotateRight(root);
	}
	else if(bf <= -2){
		if(rightBf > 0){
			root->right = rotateRight(root->right);
		}
		root = rotateLeft(root);
	}

	return root;
}

void readDB(Node* root) {
	if (!root) {
		return;
	}
	readDB(root->left);
	printf("Name: %s, Phone Number: %s\n", root->name, root->phoneNumber);
	readDB(root->right);
}

Node* findNode(Node* root, const char* name) {
	if (!name) {
		fprintf(stderr, "Invalid name parameter passed to findNode.\n");
		return NULL;
	}
	while (root) {
		if (strcmp(name, root->name) == 0) {
			return root;
		}
		else if (strcmp(name, root->name) < 0) {
			root = root->left;
		}
		else {
			root = root->right;
		}
	}
	return NULL;
}

Node* findSuccessor(Node* root) {
	if (!root || !root->right) {
		fprintf(stderr, "node does not exist or no successor found for the given node.\n");
		return NULL;
	}
	Node* current = root->right;
	while (current->left) {
		current = current->left;
	}
	return current;
}

Node* rotateRight(Node* root) {
	assert(root != NULL);
	assert(root->left != NULL);

	Node* temp = root->left;
	root->left = temp->right;
	temp->right = root;
	root = temp;
	root->right->height = setHeight(root->right);
	root->height = setHeight(root);	

	return root;
}

Node* rotateLeft(Node* root) {
	assert(root != NULL);;
	assert(root->right != NULL);

	Node* temp = root->right;
	root->right = temp->left;
	temp->left = root;
	root = temp;
	root->left->height = setHeight(root->left);
	root->height = setHeight(root);

	return root;
}