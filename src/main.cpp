#include <iostream>

#include "headers/assist.h"
#include "headers/Snake.h"



/* Windowe dimensions */
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

/* Global window */
SDL_Window* window = nullptr;
/* Global renderer */
SDL_Renderer* renderer = nullptr;


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


	/* Load media */
	loadMedia(backgroundTexture, snakeTexture);
	
	/* Close flag */
	bool quit = false;
	/* Event variable */
	SDL_Event event;

	/* Create the snake */
	Snake snake(&snakeTexture, { 0, 0, 32, 32 }, { 32, 0, 32, 32 }, { 64, 0, 32, 32 }, 
		32, 32, 352, 256, 180.0);

	Snake_direction currentDirection = Snake_direction::STAY;

	/* Game loop */
	while (!quit) {
		/* Poll all events */
		while (SDL_PollEvent(&event)) {
			/* If user closed the application set the close flag to true */
			if (event.type == SDL_QUIT)
				quit = true;
			

			/* Move the Snake based on the key */
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					currentDirection = Snake_direction::UP;
					break;
				case SDLK_DOWN:
					currentDirection = Snake_direction::DOWN;
					break;
				case SDLK_LEFT:
					currentDirection = Snake_direction::LEFT;
					break;
				case SDLK_RIGHT:
					currentDirection = Snake_direction::RIGHT;
					break;
				}
			}
		}

		snake.move(currentDirection);

		/* Render background */
		backgroundTexture.render(0, 0);

		/* Render snake */
		snake.render();

		SDL_RenderPresent(renderer);
	}

	/* Cleanup */
	close();
	return 0;
}