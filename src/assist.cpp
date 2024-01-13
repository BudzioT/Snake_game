#include "headers/assist.h"
#include "SDL_image.h"

#include <stdio.h>


bool initialize()
{
	/* Initialize SDL video */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initialize SDL video! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	/* Initialize PNG Loading */
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("Couldn't initialize PNG loading! IMG_Error: %s\n", IMG_GetError());
		return false;
	}

	/* Create window */
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		printf("Couldn't create window! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	/* Create renderer with VSync */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		printf("Couldn't create renderer! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	/* Initialize renderer color */
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	return true;
}

bool loadMedia(Texture& background, Texture& snakeTexture)
{
	/* Success flag */
	bool success = true;

	/* Load the background */
	if (!background.loadFromFile("images/background.png")) {
		printf("Couldn't load the background texture!\n");
		success = false;
	}

	/* Load the snake texture, set color key to green */
	SDL_Color green = { 0x00, 0xFF, 0x00, 0xFF };
	if (!snakeTexture.loadFromFile("images/Snake-texture.png", &green)) {
		printf("Couldn't load the snake texture!\n");
		success = false;
	}

	return success;
}

void close()
{
	/* Destroy window */
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	/* Destroy renderer */
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	/* Quit the libraries */
	SDL_Quit();
	IMG_Quit();
}