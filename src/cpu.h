#include <stdio.h>

int start(FILE* filePtr);
static int initialize(unsigned short int* pcPtr, unsigned char* delayPtr, unsigned char* soundPtr, unsigned short int* memPtr, FILE* filePtr);
static void font(unsigned short int* memPtr);
static int game();
