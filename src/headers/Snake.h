#pragma once
#include "SnakeSegment.h"

#include <vector>

/* Directions snake can go in */
enum class Snake_direction {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	STAY
};


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

	/* Is snake dead */
	bool isDead() const;

	/* Move the snake in the given direction */
	void move(Snake_direction direction);

	/* Grow the body by one segment */
	void grow();

private:
	/* Check head segment collisions with wall */
	bool collisionWall() const;
	/* Check head segment collisions with the rest of the snake's body */
	bool collisionBody() const;

private:
	std::vector<SnakeSegment> m_body;
	
	Texture* m_texture;
	SDL_Rect m_clips[3];

	bool m_dead;
	
	Snake_direction m_direction;
};