#include "headers/Game.h"

Game::Game(Texture* snakeTexture, Texture* foodTexture,
	const SDL_Rect snakeClips[3], int blockWidth, int blockHeight, int mapHeight, int mapWidth,
	int mapX, int mapY, int snakeX, int snakeY)
	: m_snake(snakeTexture, snakeClips[0], snakeClips[1], snakeClips[2], blockWidth, blockHeight, 
		snakeX, snakeY, 180.0), m_food(foodTexture, 0, 0, blockWidth, blockHeight),
		m_currentDirection(Snake_direction::STAY), m_timerID(0), m_speed(150),
		m_gen(m_device()), m_randX(0, mapWidth / blockWidth - 1), m_randY(0, mapHeight / blockHeight - 1)
{
	/* Set map dimensions */
	m_snake.setMap({ mapX, mapY, mapHeight, mapWidth });

	/* Change the food position until it's out of the snake's body */
	do {
		m_food.changePosition(m_randX(m_gen), m_randY(m_gen));
	} while (m_snake.elementCollisionBody(m_food.getPosX(), m_food.getPosY()));
}

void Game::render()
{
	/* Render food */
	m_food.render();
	/* Render snake above the food */
	m_snake.render();
}

void Game::start()
{
	/* Make the snake move in the given direction */
	m_timerID = SDL_AddTimer(m_speed, &Game::snakeMove_callback, this);
}

void Game::changeSpeed(Uint32 speed)
{
	m_speed = speed;
}

Uint32 Game::snakeMove(Uint32 interval)
{
	/* Move the snake in the given direction */
	m_snake.move(m_currentDirection);
	/* Return the same speed for the next movement */
	return m_speed;
}

Uint32 Game::snakeMove_callback(Uint32 interval, void* param)
{
	/* Call the snakeMove function on the given game */
	return (reinterpret_cast<Game*>(param)->snakeMove(interval));
}