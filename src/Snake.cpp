#include "headers/Snake.h"

Snake::Snake(Texture* texture, const SDL_Rect& headClip, const SDL_Rect& bodyClip, const SDL_Rect& tailClip, 
	int width, int height, int posX, int posY, double angle) : m_texture(texture)
{
	/* Set clips */
	m_clips[0] = headClip;
	m_clips[1] = bodyClip;
	m_clips[2] = tailClip;

	/* Create and initialize head */
	m_body.emplace_back(posX, posY, angle);
	m_body[0].setWidth(width);
	m_body[0].setHeight(height);
	m_body[0].setHead(true);
	m_body[0].setTexture(m_texture);

	/* Create tail */
	m_body.emplace_back(posX - width, posY, angle);
	m_body[1].setTail(true);
}

Snake::~Snake()
{
}

void Snake::render()
{
	/* Render head */
	m_body[0].render(&m_clips[0]);

	/* Render body */
	int tail_index = m_body.size() - 1;
	for (int i = 1; i < tail_index; i++)
		m_body[i].render(&m_clips[1]);

	/* Render tail */
	m_body[tail_index].render(&m_clips[2]);
}