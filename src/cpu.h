#include <stdio.h>

int start(FILE* filePtr);
int initialize(unsigned short* pcPtr, unsigned char* delayPtr, unsigned char* soundPtr, unsigned short* memPtr, FILE* filePtr);
void font(unsigned short* memPtr);
int game(FILE* filePtr, unsigned short* memPtr);
