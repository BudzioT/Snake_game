#include <iostream>
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

/* Window dimensions */
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 700;


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

	/* Map start points */
	int mapX = (WINDOW_WIDTH - GAME_WIDTH) / 2;
	int mapY = (WINDOW_HEIGHT - GAME_HEIGHT) / 2;


	/* Load media */
	loadMedia(backgroundTexture, snakeTexture, foodTexture, &eatSound, &hitWall, &hitBody, headerText, 
		subText);

	/* Snake clips */
	SDL_Rect snakeClips[3] = {
		{ 0, 0, 32, 32 },
		{ 32, 0, 32, 32 },
		{ 64, 0, 32, 32 }
	};

	/* Close flag */
	bool quit = false;
	/* Start screen flag */
	bool startScreen = true;
	/* Game over flag */
	bool gameOver = false;

	/* Create the game */
	Game game(&snakeTexture, &foodTexture, snakeClips, gameOver, 32, 32, 640, 480, mapX, mapY, 
		352 + mapX, 256 + mapY);


	/* Initialize the rest of the game */
	game.addSounds(*eatSound, *hitWall, *hitBody);
	game.addText(headerText, subText);
	game.addBackground(backgroundTexture);


	/* Event variable */
	SDL_Event event;

	/* Game loop */
	while (!quit) {
		/* If the game is starting */
		if (startScreen) {
			/* Set the right text */
			headerText.loadFromText("Welcome to the Snake Game!", headerFont, { 200, 0, 0 });
			subText.loadFromText("Click Enter to start!", subFont, { 9, 75, 97 });

			/* Starter screen loop */
			while (startScreen) {
				/* Poll events */
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						startScreen = false;
						quit = true;
					}

					if (event.type == SDL_KEYDOWN) {
						switch (event.key.keysym.sym) {
							/* On 'enter' click, end the start screen, start the game */
						case SDLK_RETURN:
							startScreen = false;
							game.start(352 + mapX, 256 + mapY);
							break;
							/* On 'escape' click, exit the game */
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
		}

		/* If the game has ended */
		else if (gameOver) {
			/* Set the right text */
			headerText.loadFromText("GAME OVER!", headerFont, { 200, 0, 0 });
			subText.loadFromText("Click Enter to play again!", subFont, { 9, 75, 97 });

			/* Game over screen loop */
			while (gameOver) {
				/* Poll events */
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						gameOver = false;
						quit = true;
					}

					if (event.type == SDL_KEYDOWN) {
						switch (event.key.keysym.sym) {
							/* On 'enter' click, go to the start screen */
						case SDLK_RETURN:
							gameOver = false;
							startScreen = true;
							break;
							/* On 'escape' click, exit the game */
						case SDLK_ESCAPE:
							gameOver = false;
							quit = true;
						}
					}
				}

				/* Render the GameOver screen */
				game.gameOver();

				/* Clear renderer */
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderPresent(renderer);
			}
		}
		
		else {
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

			/* Render game */
			game.render();

			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderPresent(renderer);
		}
	}

	/* Cleanup */
	close(&eatSound, &hitWall, &hitBody);
	return 0;
}