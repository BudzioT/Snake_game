#include "headers/Texture.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

Texture::Texture() : m_texture(nullptr), m_width(0), m_height(0)
{
}

Texture::~Texture()
{
	/* Deallocate */
	free();
}

bool Texture::loadFromFile(const std::string& path, SDL_Color* colorKey)
{
	/* Destroy previous texture */
	free();

	/* Load image */
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (!loadedSurface) {
		printf("Couldn't load image from %s! IMG_Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}
	
	/* If color key is given, set it */
	if (colorKey) {
		SDL_SetColorKey(loadedSurface, SDL_TRUE,
			SDL_MapRGBA(loadedSurface->format, colorKey->r, colorKey->g, colorKey->b, colorKey->a));
	}

	/* Create texture from surface pixels */
	m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (!m_texture)
		printf("Couldn't create texture from %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
	/* Save new dimensions */
	else {
		m_width = loadedSurface->w;
		m_height = loadedSurface->h;
	}

	/* Cleanup */
	SDL_FreeSurface(loadedSurface);
	
	/* Return success */
	return m_texture;
}

bool Texture::loadFromText(const std::string& text, TTF_Font* font, SDL_Color color)
{
	/* Cleanup preexisiting texture */
	free();

	/* Load text */
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (!textSurface) {
		printf("Couldn't load text surface! TTF_Error: %s\n", TTF_GetError());
		return false;
	}

	/* Create texture from surface pixels */
	m_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!m_texture)
		printf("Couldn't create texture from text surface! SDL_Error: %s\n", SDL_GetError());
	/* Save new dimensions */
	else {
		m_width = textSurface->w;
		m_height = textSurface->h;
	}

	/* Cleanup */
	SDL_FreeSurface(textSurface);

	/* Return success */
	return m_texture;
}

void Texture::free()
{
	/* If texture exists */
	if (m_texture) {
		/* Free the actual texture */
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;

		/* Reset dimensions */
		m_width = 0;
		m_height = 0;
	}
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	/* Set rendering space */
	SDL_Rect renderQuad = { x, y, m_width, m_height };

	/* Set the clip dimensions if it exists */
	if (clip) {
		m_width = clip->w;
		m_height = clip->h;
	}

	/* Render to screen */
	SDL_RenderCopyEx(renderer, m_texture, clip, &renderQuad, angle, center, flip);
}

int Texture::width() const
{
	return m_width;
}

int Texture::height() const
{
	return m_height;
}