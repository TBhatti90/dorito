#include <stdio.h>

int cpu() {
	//RAM
	unsigned char mem[4096] = {0};
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
	unsigned short int stack[16] = {0};



	return 0;
}
