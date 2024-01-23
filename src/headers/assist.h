#pragma once
#include "SDL.h"
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
bool loadMedia(Texture& background, Texture& snakeTexture, Texture& foodTexture);

/* Clean up before closing */
void close();