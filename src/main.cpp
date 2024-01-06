#include <iostream>

#include "headers/assist.h"


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


	/* Load media */
	loadMedia(backgroundTexture);
	
	/* Close flag */
	bool quit = false;
	/* Event variable */
	SDL_Event event;

	/* Game loop */
	while (!quit) {
		/* Poll all events */
		while (SDL_PollEvent(&event)) {
			/* If user closed the application set the close flag to true */
			if (event.type == SDL_QUIT)
				quit = true;
		}

		backgroundTexture.render(0, 0);
		SDL_RenderPresent(renderer);
	}

	/* Cleanup */
	close();
	return 0;
}