#include "SDL.h"

/* Window dimensions */
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;


/* Initialize SDL libraries, window */
bool initialize(SDL_Window* window);

/* Clean up before closing */
void close(SDL_Window* window);