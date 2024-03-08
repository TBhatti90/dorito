#include "cpu.h"

int start(FILE* filePtr) {
	//RAM
	unsigned short mem[4096] = {0};
	//Registers
	unsigned char V[16] = {0};
	//Address Register
	unsigned char I = 0;
	//Delay and Sound Timers
	unsigned char delay = 0;
	unsigned char sound = 0;
	//Program Counter
	unsigned short int PC = 0;
	//Stack Pointer
	unsigned char SP = 0;
	//Stack
	unsigned short stack[16] = {0};
	//Error checking
	int e = 0;

	//Initialize
	if ((e = initialize(&PC, &delay, &sound, mem, filePtr)) != 0) {
		return -1;
	}

	//Fetch, Decode, and Execute
	while(1) {
		break;
	}

	return 0;
}

int initialize(unsigned short* pcPtr, unsigned char* delayPtr, unsigned char* soundPtr, unsigned short* memPtr, FILE* filePtr) {
	//Setting PC to proper memory location
	*pcPtr = 0x200;

	//Setting timers
	*delayPtr = 60;
	*soundPtr = 60;

	//Placing font into memory
	font(memPtr);

	//Placing game into memory
	if (game(filePtr, memPtr) == -1) {
		return -1;
	}
	
	return 0;
}

void font(unsigned short* memPtr) {
	//0
	*(memPtr + 0x50) = 0xF0, *(memPtr + 0x51) = 0x90, *(memPtr + 0x52) = 0x90, *(memPtr + 0x53) = 0x90, *(memPtr + 0x54) = 0xF0;
	//1
	*(memPtr + 0x55) = 0x20, *(memPtr + 0x56) = 0x60, *(memPtr + 0x57) = 0x20, *(memPtr + 0x58) = 0x20, *(memPtr + 0x59) = 0x70;
	//2
	*(memPtr + 0x5A) = 0xF0, *(memPtr + 0x5B) = 0x10, *(memPtr + 0x5C) = 0xF0, *(memPtr + 0x5D) = 0x80, *(memPtr + 0x5E) = 0xF0;
	//3
	*(memPtr + 0x5F) = 0xF0, *(memPtr + 0x60) = 0x10, *(memPtr + 0x61) = 0xF0, *(memPtr + 0x62) = 0x10, *(memPtr + 0x63) = 0xF0;
	//4
	*(memPtr + 0x64) = 0x90, *(memPtr + 0x65) = 0x90, *(memPtr + 0x66) = 0xF0, *(memPtr + 0x67) = 0x10, *(memPtr + 0x68) = 0x10;
	//5
	*(memPtr + 0x69) = 0xF0, *(memPtr + 0x6A) = 0x80, *(memPtr + 0x6B) = 0xF0, *(memPtr + 0x6C) = 0x10, *(memPtr + 0x6D) = 0xF0;
	//6
	*(memPtr + 0x6E) = 0xF0, *(memPtr + 0x6F) = 0x80, *(memPtr + 0x70) = 0xF0, *(memPtr + 0x71) = 0x90, *(memPtr + 0x72) = 0xF0;
	//7
	*(memPtr + 0x73) = 0xF0, *(memPtr + 0x74) = 0x10, *(memPtr + 0x75) = 0x20, *(memPtr + 0x76) = 0x40, *(memPtr + 0x77) = 0x40;
	//8
	*(memPtr + 0x78) = 0xF0, *(memPtr + 0x79) = 0x90, *(memPtr + 0x7A) = 0xF0, *(memPtr + 0x7B) = 0x90, *(memPtr + 0x7C) = 0xF0;
	//9
	*(memPtr + 0x7D) = 0xF0, *(memPtr + 0x7E) = 0x90, *(memPtr + 0x7F) = 0xF0, *(memPtr + 0x80) = 0x10, *(memPtr + 0x81) = 0xF0;
	//A
	*(memPtr + 0x82) = 0xF0, *(memPtr + 0x83) = 0x90, *(memPtr + 0x84) = 0xF0, *(memPtr + 0x85) = 0x90, *(memPtr + 0x86) = 0x90;
	//B
	*(memPtr + 0x87) = 0xE0, *(memPtr + 0x88) = 0x90, *(memPtr + 0x89) = 0xE0, *(memPtr + 0x8A) = 0x90, *(memPtr + 0x8B) = 0xE0;
	//C
	*(memPtr + 0x8C) = 0xF0, *(memPtr + 0x8D) = 0x80, *(memPtr + 0x8E) = 0x80, *(memPtr + 0x8F) = 0x80, *(memPtr + 0x90) = 0xF0;
	//D
	*(memPtr + 0x91) = 0xE0, *(memPtr + 0x92) = 0x90, *(memPtr + 0x93) = 0x90, *(memPtr + 0x94) = 0x90, *(memPtr + 0x95) = 0xE0;
	//E
	*(memPtr + 0x96) = 0xF0, *(memPtr + 0x97) = 0x80, *(memPtr + 0x98) = 0xF0, *(memPtr + 0x99) = 0x80, *(memPtr + 0x9A) = 0xF0;
	//F
	*(memPtr + 0x9B) = 0xF0, *(memPtr + 0x9C) = 0x80, *(memPtr + 0x9D) = 0xF0, *(memPtr + 0x9E) = 0x80, *(memPtr + 0x9F) = 0x80;
}

int game(FILE* filePtr, unsigned short* memPtr) {
	//Getting file size
	if (fseek(filePtr, 0, SEEK_END) != 0) {
		return -1;
	}
	unsigned long fileSize = 0;
	if ((fileSize = ftell(filePtr)) < 0) {
		return -1;
	}
	if (fseek(filePtr, 0, SEEK_SET) != 0) {
		return -1;
	}
	//Reading file
	unsigned long count = fread((memPtr + 0x200), 1, fileSize, filePtr);
	//Checking if EOF or error during read
	if (count < fileSize) {
		if (ferror(filePtr)) {
			return -1;
		}
	}

	if (fclose(filePtr) == EOF) {
		return -1;
	}

	return 0;
}
