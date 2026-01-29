#ifndef MENU_H
#define MENU_H
#include "tree.h"

void menu(const char* filename);
void displayMenu();
int handleChoice(int choice, Node** DBroot, FILE* file);
void exitDBProcess(FILE* file, Node* DBroot);
void writeInFile(FILE* file, Node* root);

#endif
