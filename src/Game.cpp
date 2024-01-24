#include "headers/Game.h"

Game::Game(Texture* snakeTexture, Texture* foodTexture,
	const SDL_Rect snakeClips[3], int blockWidth, int blockHeight, int mapHeight, int mapWidth,
	int mapX, int mapY, int snakeX, int snakeY)
	: m_snake(snakeTexture, snakeClips[0], snakeClips[1], snakeClips[2], blockWidth, blockHeight, 
		snakeX, snakeY, 180.0), m_food(foodTexture, 0, 0, blockWidth, blockHeight),
		m_currentDirection(Snake_direction::STAY), m_timerID(0),
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