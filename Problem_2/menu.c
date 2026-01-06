#include <stdio.h>
#include <stdlib.h>	
#include "menu.h"
#include "data_base.h"

void continueOps(char* again) {
	printf("Do you want to do another operation? (y/n): ");
	(void)scanf(" %c", again);
	if (*again == 'n') {
		printf("Exiting the menu. Goodbye!\n");
		return;
	}
}

void menu(size_t hashSize, const char* filename) {
	List* inmemDb = NULL;
	char again = 'y';
	FILE* file = NULL;
	int data;
	printf("Welcome to your DB menu:\n");
	while (again == 'y') {
		printf("What operation do you want to perform?\n");
		printf("1. Store a batch of data into the database\n");
		printf("2. Add data to the database\n");
		printf("3. Search for data\n");
		printf("4. Read the whole database\n");
		printf("5. Exit\n");

		Option choice;
		(void)scanf("%d", &choice);
		switch (choice) {
		case STORE:
			printf("You chose to store a batch of data into the database.\n");
			printf("Enter the number of elements you want to store: ");
			int arrSize;
			(void)scanf("%d", &arrSize);
			printf("Enter the elements:\n");
			int* req = requestArrData(arrSize);
			file = fopen(filename, "w");
			storeData(req, arrSize, file);
			free(req);
			fclose(file);
			continueOps(&again);
			break;
		case ADD:
			printf("You chose to add data to the database.\n");
			printf("Enter the data you want to add: ");
			(void)scanf("%d", &data);
			if (!inmemDb) {
				file = fopen(filename, "r");
				inmemDb = createDataBase(hashSize, file);
				fclose(file);
			}
			file = fopen(filename, "a");
			addData(data, file, inmemDb);
			fclose(file);
			continueOps(&again);
			break;
		case SEARCH:
			printf("You chose to search for data.\n");
			printf("Enter the data you want to search for: ");
			(void)scanf("%d", &data);
			if (!inmemDb) {
				file = fopen(filename, "r");
				inmemDb = createDataBase(hashSize, file);
				fclose(file);
			}
			int searchIndex = searchInHash(inmemDb, data);
			if(searchIndex == -1)
				printf("Data %d not found in the database.\n", data);
			else
				printf("Data %d is found in the bucket No.%d of the database.\n", data, searchIndex);
			continueOps(&again);
			break;
		case READ:
			printf("You chose to read the whole database.\n");
			printf("Here is the content of the database:\n");
			file = fopen(filename, "r");
			displayDB(file);
			fclose(file);
			continueOps(&again);
			break;
		case EXIT:
			free(inmemDb);
			printf("Exiting the menu. Goodbye!\n");
			return;
		default:
			printf("Invalid choice. Please try again.\n");
		}
	}
}