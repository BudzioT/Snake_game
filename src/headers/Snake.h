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
	/* Is the death reason hitting a wall */
	bool isDeadByWall() const;

	/* Move the snake in the given direction */
	void move(Snake_direction direction);

	/* Grow the body by one segment */
	void grow();

	/* Get head X axis position */
	int getPosX() const;
	/* Get head Y axis position */
	int getPosY() const;

	/* Change map position and dimensions */
	void setMap(SDL_Rect newMap);
	/* Change map dimensions */
	void setMapDimensions(int width, int height);
	/* Change map positions */
	void setMapPositions(int posX, int posY);

	/* Check given element collision with snake's body */
	bool elementCollisionBody(int posX, int posY) const;

private:
	/* Check head segment collisions with wall */
	bool collisionWall();
	/* Check head segment collisions with the rest of the snake's body */
	bool collisionBody() const;

private:
	/* Body - several segments */
	std::vector<SnakeSegment> m_body;
	
	/* Texture */
	Texture* m_texture;
	/* Texture clips for: head, body, tail */
	SDL_Rect m_clips[3];

	/* Gameover flag */
	bool m_dead;
	bool m_wall;
	
	/* Direction snake is moving in */
	Snake_direction m_direction;

	/* Map dimensions */
	SDL_Rect m_map;
};