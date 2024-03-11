#include "cpu.h"

//Start of Emulation cycle
int start(FILE* filePtr) {
	//RAM
	unsigned char mem[4096] = {0};
	//Registers
	unsigned char V[16] = {0};
	//Address Register
	unsigned short* I = 0;
	//Delay and Sound Timers
	unsigned char delay = 0;
	unsigned char sound = 0;
	//Program Counter
	unsigned short* PC = 0;
	//Stack Pointer
	unsigned char* SP = 0;
	//Stack
	unsigned short stack[16] = {0};
	//Error checking
	int e = 0;
	//Random number seed
	srand(time(NULL));

	//Initialize
	if ((e = initialize(PC, &delay, &sound, mem, filePtr)) != 0) {
		return -1;
	}

	//Fetch, Decode, and Execute
	while(1) {
		unsigned short instruction = fetch(mem, PC);
		decode_and_execute(&instruction, PC, SP, V, stack, I);
		break;
	}

	return 0;
}

//Initialize emulator variables and place font and game data into RAM
int initialize(unsigned short* PC, unsigned char* delayPtr, unsigned char* soundPtr, unsigned char mem[], FILE* filePtr) {
	//Setting PC to proper memory location
	*PC = 0x200;

	//Setting timers
	*delayPtr = 60;
	*soundPtr = 60;

	//Placing font into memory
	font(mem);

	//Placing game into memory
	if (game(filePtr, mem) == -1) {
		return -1;
	}
	
	return 0;
}

//Place font data into RAM
void font(unsigned char mem[]) {
	//0
	mem[0x50] = 0xF0, mem[0x51] = 0x90, mem[0x52] = 0x90, mem[0x53] = 0x90, mem[0x54] = 0xF0;
	//1
	mem[0x55] = 0x20, mem[0x56] = 0x60, mem[0x57] = 0x20, mem[0x58] = 0x20, mem[0x59] = 0x70;
	//2
	mem[0x5A] = 0xF0, mem[0x5B] = 0x10, mem[0x5C] = 0xF0, mem[0x5D] = 0x80, mem[0x5E] = 0xF0;
	//3
	mem[0x5F] = 0xF0, mem[0x60] = 0x10, mem[0x61] = 0xF0, mem[0x62] = 0x10, mem[0x63] = 0xF0;
	//4
	mem[0x64] = 0x90, mem[0x65] = 0x90, mem[0x66] = 0xF0, mem[0x67] = 0x10, mem[0x68] = 0x10;
	//5
	mem[0x69] = 0xF0, mem[0x6A] = 0x80, mem[0x6B] = 0xF0, mem[0x6C] = 0x10, mem[0x6D] = 0xF0;
	//6
	mem[0x6E] = 0xF0, mem[0x6F] = 0x80, mem[0x70] = 0xF0, mem[0x71] = 0x90, mem[0x72] = 0xF0;
	//7
	mem[0x73] = 0xF0, mem[0x74] = 0x10, mem[0x75] = 0x20, mem[0x76] = 0x40, mem[0x77] = 0x40;
	//8
	mem[0x78] = 0xF0, mem[0x79] = 0x90, mem[0x7A] = 0xF0, mem[0x7B] = 0x90, mem[0x7C] = 0xF0;
	//9
	mem[0x7D] = 0xF0, mem[0x7E] = 0x90, mem[0x7F] = 0xF0, mem[0x80] = 0x10, mem[0x81] = 0xF0;
	//A
	mem[0x82] = 0xF0, mem[0x83] = 0x90, mem[0x84] = 0xF0, mem[0x85] = 0x90, mem[0x86] = 0x90;
	//B
	mem[0x87] = 0xE0, mem[0x88] = 0x90, mem[0x89] = 0xE0, mem[0x8A] = 0x90, mem[0x8B] = 0xE0;
	//C
	mem[0x8C] = 0xF0, mem[0x8D] = 0x80, mem[0x8E] = 0x80, mem[0x8F] = 0x80, mem[0x90] = 0xF0;
	//D
	mem[0x91] = 0xE0, mem[0x92] = 0x90, mem[0x93] = 0x90, mem[0x94] = 0x90, mem[0x95] = 0xE0;
	//E
	mem[0x96] = 0xF0, mem[0x97] = 0x80, mem[0x98] = 0xF0, mem[0x99] = 0x80, mem[0x9A] = 0xF0;
	//F
	mem[0x9B] = 0xF0, mem[0x9C] = 0x80, mem[0x9D] = 0xF0, mem[0x9E] = 0x80, mem[0x9F] = 0x80;
}

//Place game data into RAM
int game(FILE* filePtr, unsigned char mem[]) {
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
	unsigned long count = fread((mem + 0x200), 1, fileSize, filePtr);
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

//Fetch opcode, of game data, from RAM
unsigned short fetch(unsigned char mem[], unsigned short* PC) {
	unsigned short byte1 = mem[*PC];
	unsigned char byte2 = mem[*PC+1];
	byte1 <<= 8;
	unsigned short instruction = byte1 | byte2;
	*PC += 2;

	return instruction;
}

//Decode and Execute instruction of game data, from RAM
int decode_and_execute(unsigned short* instructionPtr, unsigned short* PC, unsigned char* SP, unsigned char V[], unsigned short stack[], unsigned short* I) {
	unsigned short nnn = *instructionPtr & 0x0FFF;
	unsigned char n = *instructionPtr & 0x000F;
	unsigned char x = *instructionPtr & 0x0F00;
	unsigned char y = *instructionPtr & 0x00F0;
	unsigned char kk = *instructionPtr & 0x00FF;
	unsigned char z = *instructionPtr & 0xF000;
	unsigned short carryCheck = 0;
	unsigned char randomByte = rand() % 256;

	switch (z) {
		case 0x0:
			//Clears the screen. TODO: needs gpu
			if (*instructionPtr == 0x00E0) {
				//clear();
			//Returns from subroutine. Set PC to address at top of stack, subtract 1 from SP.
			} else if (*instructionPtr == 0x00EE) {
				*PC = stack[*SP];
				--*SP;
			//Jumps to a machine code routine at nnn. Only used for Cosmic VIP compatiblity.
			} else {
				//TODO: implement for backwards compatiblity.
			}
			break;
		//Jumps to nnn. Sets PC to nnn.
		case 0x1:
			*PC = nnn;
			break;
		//Calls subroutine at nnn. Increments the SP, puts current PC at top of stack, PC set to nnn.
		case 0x2:
			++*SP;
			stack[*SP] = *PC;
			*PC = nnn;
			break;
		//Skips next instruction if Vx = kk. If Vx == kk, increment PC by 2.
		case 0x3:
			if (V[x] == kk) {
				*PC += 2;
			}
			break;
		//Skips next instruction if Vx != kk. If Vx != kk, increment PC by 2.
		case 0x4:
			if (V[x] != kk) {
				*PC += 2;
			}
			break;
		//Skips next instruction if Vx = Vy. If Vx = Vy, increment PC by 2.
		case 0x5:
			if (V[x] == V[y]) {
				*PC += 2;
			}
			break;
		//Puts kk into Vx.
		case 0x6:
			V[x] = kk;
			break;
		//Adds kk to Vx, stores result into Vx.
		case 0x7:
			V[x] += kk;
			break;
		case 0x8:
			switch (n) {
				//Stores Vy into Vx.
				case 0x0:
					V[x] = V[y];
					break;
				//Performs a bitwise OR on Vx and Vy, stores result in Vx.
				case 0x1:
					V[x] |= V[y];
					break;
				//Performs a bitwise AND on Vx and Vy, stores result in Vx.
				case 0x2:
					V[x] &= V[y];
					break;
				//Performs a bitwise XOR on Vx and Vy, stores result in Vx.
				case 0x3:
					V[x] ^= V[y];
					break;
				//Adds Vx and Vy, if result is greater than 255(8 bits), VF is set to 1.
				case 0x4:
					carryCheck = V[x];
					carryCheck = V[x] + V[y];
					V[x] = 0x00FF & carryCheck;
					if (carryCheck > 0x00FF) {
						V[0xF] = 1;
					} else {
						V[0xF] = 0;
					}
					break;
				//If Vx > Vy, VF set to 1. Subtracts Vy from Vx, results stored in Vx.
				case 0x5:
					if (V[x] > V[y]) {
						V[0xF] = 1;
					} else {
						V[0xF] = 0;
					}
					V[x] -= V[y];
					break;
				//If least-significant bit of of Vx is 1, VF set to 1, otherwise 0. Vx is divided by 2.
				case 0x6:
					if ((0x0F & V[x]) == 0b00000001) {
						V[0xF] = 1;
					} else {
						V[0xF] = 0;
					}
					V[x] >>= 1;
					break;
				//If Vy > Vx, VF set to 1, otherwise 0. Subracts Vx from Vy, results stored in Vx.
				case 0x7:
					if (V[y] > V[x]) {
						V[0xF] = 1;
					} else {
						V[0xF] = 0;
					}
					V[x] = V[y] - V[x];
					break;
				//If most-significant bit of Vx is 1, VF set to 1, otherwise 0. Vx multiplied by 2.
				case 0xE:
					if ((0xF0 & V[x]) == 0b10000000) {
						V[0xF] = 1;
					} else {
						V[0xF] = 0;
					}
					V[x] <<= 1;
				default:
					break;
			}
			break;
		//Skips next instruction if Vx != Vy. Increments PC by 2.
		case 0x9:
			if (V[x] != V[y]) {
				*PC += 2;
			}
			break;
		//Sets I to nnn.
		case 0xA:
			*I = nnn;
			break;
		//Jump to location nnn + V0. PC is set to nnn + V0.
		case 0xB:
			*PC = V[0] + nnn;
			break;
		//Sets Vx to random byte AND kk. Generate a random number from 0 to 255 (0x0 to 0xFF), and AND with kk. Results are stored in Vx.
		case 0xC:
			V[x] = randomByte & kk;
			break;
		//Read n-bytes from RAM, starting at address I. These bytes are displayed as sprites at location (Vx,Vy). Sprites are XORed onto the screen. If this causes any pixels to be erased, VF is set to 1, otherwise set to 0. If sprite is positioned so part of it is outside the coordinates of the display, wrap it around to the opposite side of the screen.
		case 0xD:
			//TODO: work on gpu.
			break;
		case 0xE:
			//Skip next instruction if key with the value of Vx is pressed. Check keyboard, if key corresponding to the value of Vx is in the UP position, increment PC by 2.
			if (y == 0x9) {
				//TODO: input
			//Skip next instruction if key with the value of Vx is not pressed. Check keyboard, if key corresponding to the value of Vx is in the UP position, increment PC by 2.
			} else if (y == 0xA) {
				//TODO: input
			}
			break;
		case 0xF:
			switch (y) {
				default:
					break;
			}
		default:
			break;
	}

	return 0;
}
