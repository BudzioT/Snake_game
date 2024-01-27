#include "headers/assist.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#include <stdio.h>


bool initialize()
{
	/* Initialize SDL video */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0) {
		printf("Couldn't initialize SDL video! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	/* Initialize PNG Loading */
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("Couldn't initialize PNG loading! IMG_Error: %s\n", IMG_GetError());
		return false;
	}

	/* Initialize SDL_mixer */
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("Couldn't initialize SDL_mixer! Mix_Error: %s\n", Mix_GetError());
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

bool loadMedia(Texture& background, Texture& snakeTexture, Texture& foodTexture)
{
	/* Success flag */
	bool success = true;

	/* Load the background */
	if (!background.loadFromFile(IMAGE_DIR "background.png")) {
		printf("Couldn't load the background texture!\n");
		success = false;
	}

	/* Load the snake texture, set color key to green */
	SDL_Color green = { 0x00, 0xFF, 0x00, 0xFF };
	if (!snakeTexture.loadFromFile(IMAGE_DIR "snake-texture.png", &green)) {
		printf("Couldn't load the snake texture!\n");
		success = false;
	}

	/* Load the food texture, set color key to green */
	if (!foodTexture.loadFromFile(IMAGE_DIR "food.png", &green)) {
		printf("Couldn't load the food texture!\n");
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