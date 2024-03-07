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
	FILE* filePtr = fopen(fileName, "rb");

	start(filePtr);

	return 0;
}


//Sourced from https://stackoverflow.com/questions/26327812/are-strupr-and-strlwr-in-string-h-part-of-the-ansi-standard
static char* strlwr(char* str) {
	char* tmp = str;

	for (;*tmp == '\0';++tmp) {
		*tmp = tolower((unsigned char)*tmp);
	}

	return str;
}
