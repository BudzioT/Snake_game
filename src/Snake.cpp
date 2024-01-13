#include "headers/Snake.h"

Snake::Snake(Texture* texture, const SDL_Rect& headClip, const SDL_Rect& bodyClip, const SDL_Rect& tailClip, 
	int width, int height, int posX, int posY, double angle) : m_texture(texture), m_dead(false),
	m_direction(Snake_direction::STAY)
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

void Snake::move(Snake_direction direction)
{
	/* If the snake shouldn't move */
	if (direction == Snake_direction::STAY)
		return;

	/* Set the current direction */
	m_direction = direction;

	/* Check collisions with wall */
	if (collisionWall()) {
		m_dead = true;
		return;
	}

	/* Move every segment to next position */
	for (int i = m_body.size() - 1; i > 0; i--) {
		SnakeSegment* next = &m_body[i - 1];
		m_body[i].setPosition(next->getPosX(), next->getPosY());
		m_body[i].setAngle(next->getAngle());
	}

	/* Pointer to head segment */
	SnakeSegment* head = &m_body[0];

	/* Move the head based on direction */
	switch (m_direction) {
	case Snake_direction::LEFT:
		head->posX() -= head->getWidth();
		head->setAngle(0);
		break;

	case Snake_direction::RIGHT:
		head->posX() += head->getWidth();
		head->setAngle(180);
		break;
	
	case Snake_direction::UP:
		head->posY() -= head->getHeight();
		head->setAngle(90);
		break;
	
	case Snake_direction::DOWN:
		head->posY() += head->getHeight();
		head->setAngle(270);
		break;
	}

	/* Check collisions with body */
	if (collisionBody())
		m_dead = true;
}

bool Snake::isDead() const
{
	return m_dead;
}

bool Snake::collisionWall() const
{
	return false;
}

bool Snake::collisionBody() const
{
	return false;
}