#include "assist.h"

#include <stdio.h>


bool initialize(SDL_Window* window)
{
	/* Initialize SDL video */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL video! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	/* Create window */
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		printf("Couldn't create window! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

void close(SDL_Window* window)
{
	/* Destroy window */
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	/* Quit the libraries */
	SDL_Quit();
}