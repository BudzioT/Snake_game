#pragma once
#include <random>

#include "Texture.h"
#include "Snake.h"
#include "Food.h"

/* Main game logic, it manages all the game mechanics, puts it in one, full whole */
class Game
{
	Game(Texture* snakeTexture, Texture* foodTexture, const SDL_Rect snakeClips[3],
		int blockWidth = 0, int blockHeight = 0,
		int mapHeight = 0, int mapWidth = 0, int mapX = 0, int mapY = 0, int snakeX = 0, int snakeY = 0);

	void render();

private:
	/* Player - snake */
	Snake m_snake;
	/* Food which makes snake grow */
	Food m_food;

	/* Current snake direction */
	Snake_direction m_currentDirection;
	/* Timer which calls move */
	SDL_TimerID m_timerID;

	/* Seed source for randomness */
	std::random_device m_device;
	/* Random number engine */
	std::mt19937 m_gen;
	/* X axis position distribution */
	std::uniform_int_distribution<int> m_randX;
	/* Y axis position distribution */
	std::uniform_int_distribution<int> m_randY;
};