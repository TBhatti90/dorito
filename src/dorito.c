#include "dorito.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Program expects one file name. Please exit and try again.\n");
		return -1;
	}
	char* fileName = strlwr(argv[1]);
	char* fileExtension = strstr(fileName, ".ch8");
	if (fileExtension == NULL) {
		fprintf(stderr, "Error, file is not a valid Chip-8 ROM. Please supply a correct file.\n");
		return -1;
	}

	FILE* filePtr = NULL;

	if ((filePtr = fopen(fileName, "rb")) == NULL) {
		fprintf(stderr, "Error opening file, please make sure file is readable and executabble by user.\n");
		return -1;
	}

	if (start(filePtr) == -1) {
		fprintf(stderr, "Error occurred during the operation of the program. Program terminating.\n");
		return -1;
	}

	return 0;
}


//Sourced from https://stackoverflow.com/questions/26327812/are-strupr-and-strlwr-in-string-h-part-of-the-ansi-standard
char* strlwr(char* str) {
	char* tmp = str;

	for (;*tmp == '\0';++tmp) {
		*tmp = tolower((unsigned char)*tmp);
	}

	return str;
}
