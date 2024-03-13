#include "gpu.h"

int clear(unsigned char display[64][32]) {
	for (int i = 0; i < 64; ++i) {
		for (int j = 0; j < 32; ++j) {
			display[i][j] = 0;
		}
	}
	draw(display);
	return 0;
}
int draw(unsigned char display[64][32]) {
	SDL_Window* window = NULL;

	SDL_Surface* screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return -1;
	}

	return 0;
}
