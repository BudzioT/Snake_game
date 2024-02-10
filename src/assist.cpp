#include "headers/assist.h"
#include "SDL_image.h"

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

	/* Initialize SDL_ttf */
	if (TTF_Init() == -1) {
		printf("Couldn't initialize SDL_ttf! TTF_Error: %s\n", TTF_GetError());
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

bool loadMedia(Texture& background, Texture& snakeTexture, Texture& foodTexture, Mix_Chunk** eatSound,
	Mix_Chunk** hitWall, Mix_Chunk** hitBody, Texture& headerText, Texture& subText, 
	Texture& windowBackground)
{
	/* Success flag */
	bool success = true;

	/* LOAD TEXTURES */
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

	/* Load window background texture */
	if (!windowBackground.loadFromFile(IMAGE_DIR "window_background.png")) {
		printf("Couldn't load the window background texture!\n");
		success = false;
	}

	/* LOAD SOUND EFFECTS */
	/* Load eat sound */
	*eatSound = Mix_LoadWAV(SOUND_DIR "eating.mp3");
	if (*eatSound == nullptr) {
		printf("Couldn't load the eat sound! Mix_Error: %s\n", Mix_GetError());
		success = false;
	}

	/* Load wall hit sound */
	*hitWall = Mix_LoadWAV(SOUND_DIR "wallHit.mp3");
	if (*hitWall == nullptr) {
		printf("Couldn't load the wall hit sound! Mix_Error: %s\n", Mix_GetError());
		success = false;
	}

	/* Load body hit sound */
	*hitBody = Mix_LoadWAV(SOUND_DIR "bodyHit.mp3");
	if (*hitBody == nullptr) {
		printf("Couldn't load the body hit sound! Mix_Error: %s\n", Mix_GetError());
		success = false;
	}

	/* LOAD FONTS */
	headerFont = TTF_OpenFont(FONT_DIR "main.ttf", 45);
	if (!headerFont) {
		printf("Couldn't load the header font! TTF_Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		/* Render header start text with black color */
		if (!headerText.loadFromText("Snake Game", headerFont, { 200, 0, 0 })) {
			printf("Failed to load the header start text!\n");
			success = false;
		}
	}

	subFont = TTF_OpenFont(FONT_DIR "main.ttf", 25);
	if (!subFont) {
		printf("Couldn't load the sub font! TTF_Error: %s\n", TTF_GetError());
		success = false;
	}
	else {
		/* Render sub start text with dark blue color */
		if (!subText.loadFromText("Click enter to start!", subFont, { 9, 75, 97 })) {
			printf("Failed to load the sub start text!\n");
			success = false;
		}
	}

	return success;
}

void close(Mix_Chunk** eatSound, Mix_Chunk** hitWall, Mix_Chunk** hitBody)
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
	
	/* Close fonts */
	if (headerFont) {
		TTF_CloseFont(headerFont);
		headerFont = nullptr;
	}
	if (subFont) {
		TTF_CloseFont(subFont);
		subFont = nullptr;
	}

	/* Free sounds effects */
	if (*eatSound) {
		Mix_FreeChunk(*eatSound);
		*eatSound = nullptr;
	}
	if (*hitWall) {
		Mix_FreeChunk(*hitWall);
		*hitWall = nullptr;
	}
	if (*hitBody) {
		Mix_FreeChunk(*hitBody);
		*hitBody = nullptr;
	}

	/* Quit the libraries */
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}