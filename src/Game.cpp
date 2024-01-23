#include "headers/Game.h"

Game::Game(Texture* snakeTexture, Texture* foodTexture,
	const SDL_Rect snakeClips[3], int blockWidth, int blockHeight, int mapHeight, int mapWidth,
	int mapX, int mapY, int snakeX, int snakeY)
	: m_snake(snakeTexture, snakeClips[0], snakeClips[1], snakeClips[2], blockWidth, blockHeight, 
		snakeX, snakeY), m_food(foodTexture, 0, 0, blockWidth, blockHeight), 
		m_gen(m_device()), m_randX(0, mapWidth / blockWidth - 1), m_randY(0, mapHeight / blockHeight - 1)
{
	/* Set map dimensions */
	m_snake.setMap({ mapX, mapY, mapHeight, mapWidth });
}