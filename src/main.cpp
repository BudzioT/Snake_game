#include <iostream>

#include "assist.h"


/* Windowe dimensions */
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;


int main(int argc, char* args[])
{
	SDL_Window* window = nullptr;
	initialize(window);

	/*
	SDL_Surface* surf = IMG_Load("images/file.png");
	if (!surf)
		printf("Couldn't open images/file.png");
	*/
	
	bool quit = false;
	SDL_Event event;

	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;
		}
	}

	close(window);
	return 0;
}