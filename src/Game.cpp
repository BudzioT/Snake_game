#include "headers/Game.h"

Game::Game(Texture* snakeTexture, Texture* foodTexture, const SDL_Rect snakeClips[3], bool& end, 
	int blockWidth, int blockHeight, int mapWidth, int mapHeight,
	int mapX, int mapY, int snakeX, int snakeY)
	: m_snake(snakeTexture, snakeClips[0], snakeClips[1], snakeClips[2], blockWidth, blockHeight, 
		snakeX, snakeY, 180.0), m_food(foodTexture, 0, 0, blockWidth, blockHeight),
		m_currentDirection(Snake_direction::STAY), m_timerID(0), m_speed(150), m_scoreText(),
		m_gen(m_device()), m_randX(0, mapWidth / blockWidth - 1), m_randY(0, mapHeight / blockHeight - 1),
		m_soundEating(nullptr), m_soundHitWall(nullptr), m_soundHitBody(nullptr), m_scoreFont(nullptr),
		m_headerText(nullptr), m_subText(nullptr), m_background(nullptr), m_score(0),
		m_end(end), m_startPos(snakeX, snakeY), m_map{ mapX, mapY, mapWidth, mapHeight }
{
	/* Set map dimensions */
	m_snake.setMap(m_map);

	/* Food dimensions */
	int foodWidth = m_food.getWidth();
	int foodHeight = m_food.getHeight();

	/* Change the food position until it's out of the snake's body */
	do {
		m_food.changePosition(m_randX(m_gen) * foodWidth + mapX, m_randY(m_gen) * foodHeight + mapY);
	} while (m_snake.elementCollisionBody(m_food.getPosX(), m_food.getPosY()));
}

Game::~Game()
{
	SDL_RemoveTimer(m_timerID);
}

void Game::render()
{
	/* Render background if it exists */
	if (m_background)
		m_background->render(m_map.x, m_map.y);

	/* Render food */
	m_food.render();
	/* Render snake above the food */
	m_snake.render();

	/* Render score text, if it exists */
	if (m_scoreFont) {
		m_scoreText.render(400 - m_scoreText.width() / 2, 30 - m_scoreText.height() / 2);
	}
}

void Game::start(int posX, int posY)
{
	/* Set the end flag to false */
	m_end = false;

	/* Reset score */
	m_score = 0;

	/* Make Snake stay in place */
	m_currentDirection = Snake_direction::STAY;

	/* Set the snake start position */
	m_snake.restart(posX, posY, 180.0);

	/* Make the snake move in the given direction */
	m_timerID = SDL_AddTimer(m_speed, &Game::snakeMove_callback, this);

	/* Initialize score text, if it exists */
	if (m_scoreFont)
		m_scoreText.loadFromText("Score: 0", m_scoreFont, { 0xFF, 0xFF, 0xFF });
}

void Game::startScreen()
{
	/* Render header text */
	m_headerText->render(((GAME_WIDTH / 2) - (m_headerText->width() / 2) + m_map.x),
		((GAME_HEIGHT / 4) - (m_headerText->height() / 2) + m_map.y));
	/* Render sub text */
	m_subText->render(((GAME_WIDTH / 2) - (m_subText->width() / 2) + m_map.x),
		((GAME_HEIGHT / 1.5) - (m_subText->height() / 2) + m_map.y));
}

void Game::addSounds(Mix_Chunk& eating, Mix_Chunk& hitWall, Mix_Chunk& hitBody)
{
	m_soundEating = &eating;
	m_soundHitWall = &hitWall;
	m_soundHitBody = &hitBody;
}

void Game::addText(Texture& header, Texture& sub, TTF_Font& scoreFont)
{
	m_headerText = &header;
	m_subText = &sub;
	m_scoreFont = &scoreFont;

	/* Initialize score text */
	m_scoreText.loadFromText("Score: 0", m_scoreFont, { 0xFF, 0xFF, 0xFF });
}

void Game::addBackground(Texture& background)
{
	m_background = &background;
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
			posX = m_randX(m_gen) * foodWidth + m_map.x;
			posY = m_randY(m_gen) * foodHeight + m_map.y;
		} while (m_snake.elementCollisionBody(posX, posY));

		/* Play the eat sound */
		Mix_PlayChannel(-1, m_soundEating, 0);

		/* Change the position */
		m_food.changePosition(posX, posY);
		
		/* Grow the snake */
		m_snake.grow();

		/* Make the score higher, update the text */
		++m_score;
		if (m_scoreFont) {
			std::string score = "Score: " + std::to_string(m_score);
			m_scoreText.loadFromText(score.c_str(), m_scoreFont, { 0xFF, 0xFF, 0xFF });
		}
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
	
	/* Check if snake is dead */
	if (m_snake.isDead()) {
		/* If the reason is hitting a wall, play the wall hit sound effect */
		if (m_snake.isDeadByWall())
			Mix_PlayChannel(-1, m_soundHitWall, 0);
		/* If the reason is hitting a body, play the body hit sound effect */
		else
			Mix_PlayChannel(-1, m_soundHitBody, 0);
		/* End the game */
		end();
	}

	/* Return the same speed for the next movement */
	return m_speed;
}

void Game::gameOver()
{
	/* Render header text */
	m_headerText->render(((GAME_WIDTH / 2) - (m_headerText->width() / 2) + m_map.x),
		((GAME_HEIGHT / 4) - (m_headerText->height() / 2) + m_map.y));
	/* Render sub text */
	m_subText->render(((GAME_WIDTH / 2) - (m_subText->width() / 2) + m_map.x),
		((GAME_HEIGHT / 1.5) - (m_subText->height() / 2) + m_map.y));

	/* Render final score, if it exists */
	if (m_scoreFont) {
		m_scoreText.render((GAME_WIDTH / 2) - (m_scoreText.width() / 2) + m_map.x,
			(GAME_HEIGHT / 2.25) - (m_scoreText.height() / 2) + m_map.y);
	}
}

Uint32 Game::snakeMove_callback(Uint32 interval, void* param)
{
	/* Call the snakeMove function on the given game */
	return (reinterpret_cast<Game*>(param)->snakeMove(interval));
}

void Game::end()
{
	/* Set the end flag to true */
	m_end = true;

	/* Removes the game timer */
	SDL_RemoveTimer(m_timerID);
}