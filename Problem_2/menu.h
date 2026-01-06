#ifndef MENU_H
#define MENU_H

typedef enum {
	STORE = 1,
	ADD,
	SEARCH,
	READ,
	EXIT
} Option;

void menu(size_t hashSize, const char* filename);
void continueOps(char* again);

#endif
