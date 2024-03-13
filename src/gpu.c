#include "gpu.h"

int clear(unsigned char display[64][32], SDL_Window* window, SDL_Surface* screenSurface) {
	for (int i = 0; i < 64; ++i) {
		for (int j = 0; j < 32; ++j) {
			display[i][j] = 0;
		}
	}
	draw(display, window, screenSurface);
	return 0;
}
int draw(unsigned char display[64][32], SDL_Window* window, SDL_Surface* screenSurface) {

	return 0;
}
