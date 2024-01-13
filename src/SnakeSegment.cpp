#include "headers/SnakeSegment.h"

/* Initialize default dimensions of snake segment */
int SnakeSegment::m_width = 0;
int SnakeSegment::m_height = 0;

/* Initialize Snake texture to none as default */
Texture* SnakeSegment::m_texture = nullptr;


SnakeSegment::SnakeSegment(int posX, int posY, double angle) : m_posX(posX), m_posY(posY),
m_head(false), m_tail(false), m_angle(angle)
{
}

SnakeSegment::~SnakeSegment()
{
}

void SnakeSegment::render(SDL_Rect* clip)
{
	if (m_texture)
		m_texture->render(m_posX, m_posY, clip, m_angle);
}

int SnakeSegment::getPosX() const
{
	return m_posX;
}

int SnakeSegment::getPosY() const
{
	return m_posY;
}

int& SnakeSegment::posX()
{
	return m_posX;
}

int& SnakeSegment::posY()
{
	return m_posY;
}

double SnakeSegment::getAngle() const
{
	return m_angle;
}

void SnakeSegment::setWidth(int width)
{
	m_width = width;
}

void SnakeSegment::setHeight(int height)
{
	m_height = height;
}

int SnakeSegment::getWidth() const
{
	return m_width;
}

int SnakeSegment::getHeight() const
{
	return m_height;
}

void SnakeSegment::setHead(bool flag)
{
	m_head = flag;
}

void SnakeSegment::setTail(bool flag)
{
	m_tail = flag;
}

void SnakeSegment::setAngle(double angle)
{
	m_angle = angle;
}

void SnakeSegment::setPosition(int posX, int posY)
{
	m_posX = posX;
	m_posY = posY;
}

bool SnakeSegment::isThisHead() const
{
	return m_head;
}

bool SnakeSegment::isThisTail() const
{
	return m_tail;
}

void SnakeSegment::setTexture(Texture* texture)
{
	m_texture = texture;
}