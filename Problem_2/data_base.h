#ifndef DATA_BASE_H
#define DATA_BASE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hash.h"


int* createArray(int size);
int* requestArrData(int size);
int storeData(int arr[], int dataSize, FILE* file);
int addData(int data, FILE* file, List* hashTable);
List* createDataBase(size_t hashSize, FILE* file);
void displayDB(FILE* file);

#endif
