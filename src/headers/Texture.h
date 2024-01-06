#include "SDL.h"

#include <string>


/* Global window */
extern SDL_Window* window;
/* Global renderer */
extern SDL_Renderer* renderer;


class Texture
{
public:
	/* Initialize texture with basic parameters */
	Texture();
	/* Deallocate memory automatically */
	~Texture();

	/* Load texture from file at the specified path */
	bool loadFromFile(const std::string& path, SDL_Color* colorKey = nullptr);

	/* Deallocate memory */
	void free();

	/* Rneder at the given point */
	void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, 
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	/* Get width */
	int width() const;
	/* Get height */
	int height() const;

private:
	/* Actual texture */
	SDL_Texture* m_texture;

	/* Texture dimensions */
	int m_width;
	int m_height;
};