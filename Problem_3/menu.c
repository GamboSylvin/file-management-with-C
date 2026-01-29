#include <stdio.h>
#include "menu.h"

void menu(const char* filename){
	// creating the in-memDB from file
	if(!filename){
		fprintf(stderr,"Invalid filename passed to menu function.\n");
		return;
	}
	int choice;
	FILE* file = fopen(filename, "r");
	if (!file) {
		perror("Error opening file");
		return;
	}	
	Node* DBroot = createDB(file);
	if(!DBroot){
		 fprintf(stderr,"Failed to create database from file.\n");
		 fclose(file);
		 return;
	}
	fclose(file);
	// starting the menu operations
	file = fopen(filename, "w");
	if (!file) {
		perror("Error opening file");
		return;
	}
	while (1) {
		displayMenu();
		(void)scanf("%d", &choice);
		int operationState = handleChoice(choice, &DBroot, file);
		if (operationState == 1) {
			destroyDB(DBroot); // waiting implementation
			fclose(file);
			return;
		}
		else if (operationState == -1)
			continue;
		printf("Do you want to perform another operation? (yes: press any key, no: press n or N): ");
		char cont;
		(void)scanf(" %c", &cont);
		if (cont == 'n' || cont == 'N') {
			exitDBProcess(file, DBroot);
			return;
		}
	}
}

void displayMenu(){
	printf("Welcome to your Phonebook Menu:\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Update Contact\n");
	printf("4. Delete Contact\n");
	printf("5. View Contacts\n");
	printf("6. Exit\n");
	printf("Enter your choice: ");
}

int handleChoice(int choice, Node** DBroot, FILE* file){
	if (!file) {
		fprintf(stderr, "Invalid parameters passed to handleChoice.\n");
		return 1;
	}
	Node* contact = NULL;
	char name[20];
	switch (choice)
	{
		case 1:
		{
			char number[12];
			printf("Please enter the contact details to add:\n");
			printf("Name (at most 19 characters)\n");
			(void)scanf("%19s", name);
			printf("Number (11 digits)\n");
			(void)scanf("%11s", number);
			*DBroot = insertNode(*DBroot, name, number); // waiting implementation
			if(!(*DBroot)){
				fprintf(stderr,"Failed to insert the contact into the database.\n");
				return 1;
			}
			break;
		}
		case 2: 
			printf("Enter the name of the contact yoyu are searching for:\n");
			(void)scanf("%19s", name);
			contact = findNode(*DBroot, name); // waiting implementation
			if(!contact){
				printf("Contact not found in the database.\n");
				break;
			}
			printf("The contact you are searching for is:\n");
			printf("%s %s\n", contact->name, contact->phoneNumber);
			break;
		case 3:
		{
			char number[14];
			printf("Enter the name of the contact to update:\n");
			(void)scanf("%19s", name);
			contact = findNode(*DBroot, name); // waiting implementation
			if(!contact){
				printf("Contact not found in the database.\n");
				break;
			}
			printf("Enter new name (less than 19 characters):\n");
			(void)scanf("%19s", name);
			name[19] = '\0'; // ensuring null termination
			printf("Enter new number (11 digits):\n");
			(void)scanf("%11s",number);
			number[11] = '\0'; // ensuring null termination
			(void)strcpy(contact->name, name);
			(void)strcpy(contact->phoneNumber, number);
			break;
		}
		case 4:
			printf("Enter the name of the contact you want to delete:\n");
			(void)scanf("%19s", name);
			contact = findNode(*DBroot, name); // waiting implementation
			if(!contact){
				printf("Contact not found in the database.\n");
				break;
			}
			*DBroot = deleteNode(*DBroot, contact); // waiting implementation
			break;
		case 5: 
			printf("Viewing all contacts in the Phonebook:\n");
			readDB(*DBroot); // waiting implementation
			break;
		case 6:
		{
			exitDBProcess(file, *DBroot);
			return 1;
		}
		default:
			printf("Invalid choice. Please enter a number between 1 and 5: ");
			return -1;
	}
	return 0;
}

void writeInFile(FILE* file, Node* root) {
	if (!file) {
		fprintf(stderr, "no file present for writing.\n");
		return;
	}
	if (!root)
		return;
	writeInFile(file, root->left);
	fprintf(file, "%s %s\n", root->name, root->phoneNumber);
	writeInFile(file, root->right);
}

void exitDBProcess(FILE* file, Node* DBroot) {
	if (!file) {
		fprintf(stderr, "no file present for writing.\n");
		return;
	}
	printf("Exiting the Phonebook. Goodbye!\n");
	writeInFile(file, DBroot); // waiting implementation
	destroyDB(DBroot);   // waiting implementation
	fclose(file);
}