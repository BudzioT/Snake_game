#include "headers/Food.h"

/* Initialize default dimensions of food */
int Food::m_width = 0;
int Food::m_height = 0;

/* Intialize food texture to none by default */
Texture* Food::m_texture = nullptr;

Food::Food(Texture* texture, int startPosX, int startPosY, int width, int height) 
	: m_posX(startPosX), m_posY(startPosY)
{
	/* Set the texture */
	m_texture = texture;

	/* Set width and height */
	m_width = width;
	m_height = height;
}

Food::~Food()
{
}

void Food::setWidth(int width)
{
	m_width = width;
}

void Food::setHeight(int height)
{
	m_height = height;
}

int Food::getWidth() const
{
	return m_width;
}

int Food::getHeight() const
{
	return m_height;
}

void Food::setTexture(Texture* texture)
{
	m_texture = texture;
}

void Food::changePosition(int posX, int posY)
{
	m_posX = posX;
	m_posY = posY;
}

void Food::render(SDL_Rect* clip)
{
	if (m_texture)
		m_texture->render(m_posX, m_posY, clip);
}