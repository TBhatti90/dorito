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
		fprintf(stderr, "Error opening file, please make sure file is readable and executable by user.\n");
		return -1;
	}

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
		return -1;
	} else {
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			fprintf(stderr, "Window could not be created! SDL_Error %s\n", SDL_GetError());
			return -1;
		} else {
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface -> format, 0xFF, 0xFF, 0xFF));
			SDL_UpdateWindowSurface(window);
			SDL_Event e;
			bool quit = false;
			while (quit == false) {
				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}
			}
		}
	}

//	if (start(filePtr, window, screenSurface) == -1) {
//		fprintf(stderr, "Error occurred during the operation of the program. Program terminating.\n");
//		return -1;
//	}

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
