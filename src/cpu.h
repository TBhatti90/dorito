#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gpu.h"

int start(FILE* filePtr);
int initialize(unsigned short* PC, unsigned char* delayPtr, unsigned char* soundPtr, unsigned char mem[], FILE* filePtr);
void font(unsigned char mem[]);
int game(FILE* filePtr, unsigned char mem[]);
unsigned short fetch(unsigned char mem[], unsigned short* PC);
int decode_and_execute(unsigned short* instructionPtr, unsigned short* PC, unsigned char* SP, unsigned char V[], unsigned short stack[], unsigned short* I, unsigned char* delayPtr, unsigned char* soundPtr, unsigned char mem[], unsigned char display[64][32]);
