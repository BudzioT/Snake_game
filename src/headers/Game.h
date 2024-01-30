#pragma once
#include <random>

#include "SDL_mixer.h"
#include "Texture.h"
#include "Snake.h"
#include "Food.h"

/* Main game logic, it manages all the game mechanics, puts it in one, full whole */
class Game
{
public:
	Game(Texture* snakeTexture, Texture* foodTexture, const SDL_Rect snakeClips[3],
		int blockWidth = 0, int blockHeight = 0,
		int mapHeight = 0, int mapWidth = 0, int mapX = 0, int mapY = 0, int snakeX = 0, int snakeY = 0);
	~Game();

	/* Render */
	void render();

	/* Add sounds 
	Sound effects: eating, hitting wall, hitting body
	Music: theme
	*/
	void addSounds(Mix_Chunk& eating, Mix_Chunk& hitWall, Mix_Chunk& hitBody);

	/* Start the game */
	void start();

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

private:
	/* Move the snake */
	Uint32 snakeMove(Uint32 interval);
	/* Move callback */
	static Uint32 snakeMove_callback(Uint32 interval, void* param);

	/* Ends the game */
	void end();

private:
	/* Player - snake */
	Snake m_snake;
	/* Food which makes snake grow */
	Food m_food;

	/* Eating sound */
	Mix_Chunk* m_soundEating;
	/* Wall hit sound */
	Mix_Chunk* m_soundHitWall;
	/* Body hit sound */
	Mix_Chunk* m_soundHitBody;

	/* Current snake direction */
	Snake_direction m_currentDirection;
	/* Timer which calls move */
	SDL_TimerID m_timerID;

	/* Snake speed, one block every given number of miliseconds */
	Uint32 m_speed;

	/* Seed source for randomness */
	std::random_device m_device;
	/* Random number engine */
	std::mt19937 m_gen;
	/* X axis position distribution */
	std::uniform_int_distribution<int> m_randX;
	/* Y axis position distribution */
	std::uniform_int_distribution<int> m_randY;
};