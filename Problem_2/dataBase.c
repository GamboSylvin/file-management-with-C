#include <stdio.h>
#include <stdlib.h>
#include "data_base.h"

int* createArray(int size) {
	int* arr = (int*)malloc(size * sizeof(int));
	if (arr == NULL) {
		return NULL;
	}
	return arr;
}

int* requestArrData(int size) {
	int* arr = createArray(size);
	if (arr == NULL) {
		return NULL;
	}
	for (int i = 0; i < size; i++) {
		(void)scanf("%d", &arr[i]);
	}

	return arr;
}

int storeData(int arr[], int dataSize, FILE* file) {
	if (arr == NULL || file == NULL) {
		return -1;
	}
	for (int i = 0; i < dataSize; i++) {
		if (fprintf(file,"%d ", arr[i]) < 0) {
			return -1;
		}
	}
	return 0;
}

int addData(int data, FILE* file, List* hashTable) {
	if (hashTable)
		insertToHash(hashTable, data);
	else
		return -1;
	if (fprintf(file, "%d ", data) < 0) {
		return -2;
	}
	return 0;
}

List* createDataBase(size_t hashSize, FILE* file) {

	List* hashTable = calloc(hashSize, sizeof(List));

    if (!hashTable) return NULL; 
    int data;	
	
	fseek(file, 0, SEEK_SET);
    while (fscanf(file,"%d", &data) == 1) {
        uint32_t index = hash((uint32_t)data);
        appendNode(hashTable+index, data);
    }
    return hashTable;
}

void displayDB(FILE* file){
	fseek(file, 0, SEEK_SET);
	int data;	
	while (fscanf(file,"%d", &data) == 1) {
		printf("%d ", data);
	}
}