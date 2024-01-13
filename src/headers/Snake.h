#pragma once
#include "SnakeSegment.h"

#include <vector>


class Snake
{
public:
	/* Create Snake with the given texture map, which has three clips for head, body and tail.
	Initialize the segments width and height. Set the snake starting position and angle */
	Snake(Texture* texture, const SDL_Rect& headClip, const SDL_Rect& bodyClip, const SDL_Rect& tailClip, 
		int width, int height, int posX = 0, int posY = 0, double angle = 0.0);
	~Snake();

	/* Render the snake */
	void render();

	/* Move the snake in the given direction */
	void move();

	/* Grow the body by one segment */
	void grow();

private:
	std::vector<SnakeSegment> m_body;
	Texture* m_texture;
	SDL_Rect m_clips[3];
};