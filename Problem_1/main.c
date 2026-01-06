// solution to problemn 1

#include <stdio.h>

int copyFile(FILE* source, FILE* destination);
int copyBinaryFile(FILE* source, FILE* destination);

int main() {
	FILE* source = fopen("test_file.txt", "r");
	FILE* destination = fopen("copy_test_file.txt", "w");

	if (source && destination) {
		if(copyFile(source, destination) != 0)
			printf("a problem occured during the copy\n");

		fclose(source);
		fclose(destination);
	}
	FILE* binarySource = fopen("test_file.txt", "rb");
	FILE* binaryDestination = fopen("copy_test_file.txt", "wb");

	if (binarySource && binaryDestination) {
		if (copyBinaryFile(binarySource, binaryDestination) != 0)
			printf("a problem occured during the copy\n");

		fclose(binarySource);
		fclose(binaryDestination);
	}

	return 0;
}

int copyFile(FILE* source, FILE* destination) {
	char buffer[10];

	while (fgets(buffer, sizeof(buffer), source) != NULL) {
		if (fputs(buffer, destination) == EOF)
			return -1;
	}
	if (fseek(source, 1, SEEK_CUR) != 0)
		return -1;
	return 0;
}

int copyBinaryFile(FILE* source, FILE* destination) {
	char buffer[10];
	size_t bytesRead;
	while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
		if (fwrite(buffer, 1, bytesRead, destination) != bytesRead)
			return -1;
	}
	if (fseek(source, 1, SEEK_CUR) != 0)
		return -1;
	return 0;
}

