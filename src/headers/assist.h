#pragma once
#include "SDL.h"
#include "SDL_mixer.h"
#include "Texture.h"

/* Window dimensions */
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

/* Global window */
extern SDL_Window* window;
/* Global renderer */
extern SDL_Renderer* renderer;

/* Initialize SDL libraries, window */
bool initialize();

/* Loads all needed media */
bool loadMedia(Texture& background, Texture& snakeTexture, Texture& foodTexture, Mix_Chunk** eatSound, 
	Mix_Chunk** hitWall, Mix_Chunk** hitBody);

/* Clean up before closing */
void close(Mix_Chunk** eatSound = nullptr, Mix_Chunk** hitWall = nullptr, Mix_Chunk** hitBody = nullptr);