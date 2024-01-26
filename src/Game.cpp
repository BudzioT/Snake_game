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

	/* Food dimensions */
	int foodWidth = m_food.getWidth();
	int foodHeight = m_food.getHeight();

	/* Change the food position until it's out of the snake's body */
	do {
		m_food.changePosition(m_randX(m_gen) * foodWidth, m_randY(m_gen) * foodHeight);
	} while (m_snake.elementCollisionBody(m_food.getPosX(), m_food.getPosY()));
}

Game::~Game()
{
	SDL_RemoveTimer(m_timerID);
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

void Game::handleEvents(const SDL_Event& event)
{
	/* If event is of key down type */
	if (event.type == SDL_KEYDOWN) {
		/* Change the direction depending on the key */
		switch (event.key.keysym.sym) {
			/* Go up, if snake isn't going down */
		case SDLK_UP:
			if (m_currentDirection != Snake_direction::DOWN)
				m_currentDirection = Snake_direction::UP;
			break;

			/* Go down, if snake isn't going up */
		case SDLK_DOWN:
			if (m_currentDirection != Snake_direction::UP)
				m_currentDirection = Snake_direction::DOWN;
			break;

			/* Go left, if snake isn't going right */
		case SDLK_LEFT:
			if (m_currentDirection != Snake_direction::RIGHT)
				m_currentDirection = Snake_direction::LEFT;
			break;

			/* Go right, if snake isn't going left */
		case SDLK_RIGHT:
			if (m_currentDirection != Snake_direction::LEFT)
				m_currentDirection = Snake_direction::RIGHT;
			break;
		}
	}
}

void Game::process()
{
	/* Now snake position, later food position */
	int posX = m_snake.getPosX();
	int posY = m_snake.getPosY();

	/* Food dimensions */
	int foodWidth = m_food.getWidth();
	int foodHeight = m_food.getHeight();

	/* If the snakes head touches the food */
	if ((posX == m_food.getPosX()) && (posY == m_food.getPosY())) {
		/* Set food position to random until it is out of the snakes body */
		do {
			posX = m_randX(m_gen) * foodWidth;
			posY = m_randY(m_gen) * foodHeight;
		} while (m_snake.elementCollisionBody(posX, posY));

		/* Change the position */
		m_food.changePosition(posX, posY);
		
		/* Grow the snake */
		m_snake.grow();
	}
}

void Game::changeSpeed(Uint32 speed)
{
	/* Change the speed */
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