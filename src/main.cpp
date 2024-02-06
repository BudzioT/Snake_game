﻿#include <iostream>
#include <random>

#include "headers/assist.h"
#include "headers/Snake.h"
#include "headers/Food.h"
#include "headers/Game.h"

/* Global window */
SDL_Window* window = nullptr;
/* Global renderer */
SDL_Renderer* renderer = nullptr;
/* Global fonts */
TTF_Font* headerFont = nullptr;
TTF_Font* subFont = nullptr;


int main(int argc, char* args[])
{
	/* Initialize the SDL */
	if (!initialize()) {
		printf("Couldn't initialize SDL!");
		close();
		return -1;
	}


	/* Textures */
	Texture backgroundTexture;
	Texture snakeTexture;
	Texture foodTexture;

	/* Sound effects */
	Mix_Chunk* eatSound = nullptr;
	Mix_Chunk* hitWall = nullptr;
	Mix_Chunk* hitBody = nullptr;

	/* Text textures */
	Texture headerText;
	Texture subText;


	/* Load media */
	loadMedia(backgroundTexture, snakeTexture, foodTexture, &eatSound, &hitWall, &hitBody, headerText, subText);

	/* Snake clips */
	SDL_Rect snakeClips[3] = {
		{ 0, 0, 32, 32 },
		{ 32, 0, 32, 32 },
		{ 64, 0, 32, 32 }
	};

	/* Create the game */
	Game game(&snakeTexture, &foodTexture, snakeClips, 32, 32, 640, 480, 0, 0, 352, 256);


	/* Initialize the rest of the game */
	game.addSounds(*eatSound, *hitWall, *hitBody);
	game.addText(headerText, subText);

	game.start();


	/* Close flag */
	bool quit = false;
	bool startScreen = true;
	/* Event variable */
	SDL_Event event;

	/* Game loop */
	while (!quit) {
		/* Start screen rendering */
		while (startScreen) {
			/* Poll events */
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					startScreen = false;
					quit = true;
				}

				if (event.type == SDL_KEYDOWN) {
					switch (event.key.keysym.sym) {
					case SDLK_RETURN:
						startScreen = false;
						break;
					case SDLK_ESCAPE:
						startScreen = false;
						quit = true;
						break;
					}

				}
			}

			/* Render start screen */
			game.startScreen();

			/* Clear renderer */
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderPresent(renderer);
		}

		/* Poll all events */
		while (SDL_PollEvent(&event)) {
			/* If user closed the application set the close flag to true */
			if (event.type == SDL_QUIT)
				quit = true;
			/* Handle game events */
			game.handleEvents(event);
		}

		
		/* Process game logic */
		game.process();

		/* Render background */
		backgroundTexture.render(0, 0);

		/* Render game */
		game.render();

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderPresent(renderer);
	}

	/* Cleanup */
	close(&eatSound, &hitWall, &hitBody);
	return 0;
}