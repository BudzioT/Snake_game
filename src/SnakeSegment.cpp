#include "headers/SnakeSegment.h"

/* Initialize default dimensions of snake segment */
int SnakeSegment::m_width = 0;
int SnakeSegment::m_height = 0;

/* Initialize Snake texture to none as default */
Texture* SnakeSegment::m_texture = nullptr;


SnakeSegment::SnakeSegment(int posX = 0, int posY = 0, Texture* texture) : m_posX(posX), m_posY(posY),
m_head(false), m_tail(false)
{
}

SnakeSegment::~SnakeSegment()
{
}

void SnakeSegment::render(SDL_Rect* clip, double angle)
{
	m_texture->render(m_posX, m_posY, clip, angle);
}

