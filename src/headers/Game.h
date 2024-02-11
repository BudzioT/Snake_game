#pragma once
#include <random>

#include "SDL_mixer.h"
#include "Texture.h"
#include "Snake.h"
#include "Food.h"

/* Game screen dimensions */
const int GAME_WIDTH = 640;
const int GAME_HEIGHT = 480;

/* Main game logic, it manages all the game mechanics, puts it in one, full whole */
class Game
{
public:
	Game(Texture* snakeTexture, Texture* foodTexture, const SDL_Rect snakeClips[3], bool& end,
		int blockWidth = 0, int blockHeight = 0,
		int mapHeight = 0, int mapWidth = 0, int mapX = 0, int mapY = 0, int snakeX = 0, int snakeY = 0);
	~Game();

	/* Render */
	void render();

	/* Add sounds 
	Sound effects: eating, hitting wall, hitting body
	*/
	void addSounds(Mix_Chunk& eating, Mix_Chunk& hitWall, Mix_Chunk& hitBody);

	/* Add start and end text */
	void addText(Texture& header, Texture& sub, TTF_Font& scoreFont);

	/* Add static background */
	void addBackground(Texture& background);

	/* Start the game */
	void start(int posX, int posY);

	/* Start screen */
	void startScreen();

	/* Handle events */
	void handleEvents(const SDL_Event& event);

	/* Game process */
	void process();

	/* Game over screen */
	void gameOver();

	/* Change the snake speed, it moves one block per given amount of miliseconds */
	void changeSpeed(Uint32 speed);

	/* Ends the game */
	void end();

private:
	/* Move the snake */
	Uint32 snakeMove(Uint32 interval);
	/* Move callback */
	static Uint32 snakeMove_callback(Uint32 interval, void* param);
	

private:
	/* Player - snake */
	Snake m_snake;
	/* Food which makes snake grow */
	Food m_food;

	/* Snake start position */
	std::pair<int, int> m_startPos;

	/* Map dimensions */
	SDL_Rect m_map;

	/* Eating sound */
	Mix_Chunk* m_soundEating;
	/* Wall hit sound */
	Mix_Chunk* m_soundHitWall;
	/* Body hit sound */
	Mix_Chunk* m_soundHitBody;

	/* Header text */
	Texture* m_headerText;
	/* Sub text */
	Texture* m_subText;
	/* Score text */
	Texture m_scoreText;
	/* Score text */
	TTF_Font* m_scoreFont;

	/* Background texture */
	Texture* m_background;

	/* Current snake direction */
	Snake_direction m_currentDirection;
	/* Timer which calls move */
	SDL_TimerID m_timerID;

	/* Snake speed, one block every given number of miliseconds */
	Uint32 m_speed;

	/* End flag */
	bool& m_end;

	/* Score */
	int m_score;

	/* Seed source for randomness */
	std::random_device m_device;
	/* Random number engine */
	std::mt19937 m_gen;
	/* X axis position distribution */
	std::uniform_int_distribution<int> m_randX;
	/* Y axis position distribution */
	std::uniform_int_distribution<int> m_randY;
};