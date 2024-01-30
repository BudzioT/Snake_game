#include "headers/Snake.h"

Snake::Snake(Texture* texture, const SDL_Rect& headClip, const SDL_Rect& bodyClip, const SDL_Rect& tailClip, 
	int width, int height, int posX, int posY, double angle) : m_texture(texture), m_dead(false), 
	m_wall(false), m_direction(Snake_direction::STAY)
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

	/* Set map default dimensions and positions */
	m_map = { 0, 0, 640, 480 };
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

	/* Pointer to head segment */
	SnakeSegment* head = &m_body[0];

	/* Movement variables */
	int movementX = 0;
	int movementY = 0;
	int angle = head->getAngle();

	/* Set the movement variables based on direction */
	switch (m_direction) {
	case Snake_direction::LEFT:
		movementX -= head->getWidth();
		angle = 0;
		break;

	case Snake_direction::RIGHT:
		movementX += head->getWidth();
		angle = 180;
		break;

	case Snake_direction::UP:
		movementY -= head->getHeight();
		angle = 90;
		break;

	case Snake_direction::DOWN:
		movementY += head->getHeight();
		angle = 270;
		break;
	}

	/* Move the snake */
	head->posX() += movementX;
	head->posY() += movementY;

	/* If snake is out of the screen, move it back and mark it as dead */
	if (collisionWall()) {
		m_dead = true;
		head->posX() -= movementX;
		head->posY() -= movementY;
		return;
	}

	/* Move every segment besides the first one before head to next position */
	for (int i = m_body.size() - 1; i > 1; i--) {
		SnakeSegment* next = &m_body[i - 1];
		m_body[i].setPosition(next->getPosX(), next->getPosY());
		m_body[i].setAngle(next->getAngle());
	}

	/* Set the first segment before head to the old head position and angle */
	m_body[1].setPosition(head->getPosX() - movementX, head->getPosY() - movementY);
	m_body[1].setAngle(head->getAngle());

	/* Set the correct head angle */
	head->setAngle(angle);

	/* Check collisions with body */
	if (collisionBody())
		m_dead = true;
}

void Snake::grow()
{
	/* Pointer to the tail of snake */
	SnakeSegment* tail = &m_body[m_body.size() - 1];

	/* Add segment with the same values as tail */
	m_body.emplace_back(*tail);

	/* Get the tail's angle */
	int angle = static_cast<int>(tail->getAngle());
	/* Move the tail back based of angle (tail's direction) */
	switch (angle) {
	case 0:
		tail->posX() += tail->getWidth();
		break;
	case 180:
		tail->posX() -= tail->getWidth();
		break;
	case 90:
		tail->posY() -= tail->getHeight();
		break;
	case 270:
		tail->posY() += tail->getHeight();
		break;
	}
}

void Snake::setMap(SDL_Rect newMap)
{
	m_map = newMap;
}

void Snake::setMapDimensions(int width, int height)
{
	m_map.w = width;
	m_map.h = height;
}

void Snake::setMapPositions(int posX, int posY)
{
	m_map.x = posX;
	m_map.y = posY;
}

bool Snake::isDead() const
{
	return m_dead;
}

bool Snake::isDeadByWall() const
{
	return m_wall;
}

bool Snake::collisionWall()
{
	/* Pointer to snake's head */
	const SnakeSegment* head = &m_body[0];

	/* If snake's head is out of the map, there is a collision */
	if ((head->getPosX() < m_map.x) || (head->getPosX() >= (m_map.x + m_map.w))
		|| (head->getPosY() < m_map.y) || (head->getPosY() >= (m_map.y + m_map.h))) {
		m_wall = true;
		return true;
	}

	/* No collision with wall */
	return false;
}

bool Snake::collisionBody() const
{
	/* Pointer to snake's head */
	const SnakeSegment* head = &m_body[0];

	/* Get head positions */
	int headPosX = head->getPosX();
	int headPosY = head->getPosY();

	/* Go through every segment */
	for (int i = 1; i < m_body.size(); i++) {
		/* If head is inside one of the segments, there is a collision */
		if ((m_body[i].getPosX() == headPosX) && (m_body[i].getPosY() == headPosY))
			return true;
	}

	/* No collision with body */
	return false;
}

int Snake::getPosX() const
{
	return m_body[0].getPosX();
}

int Snake::getPosY() const
{
	return m_body[0].getPosY();
}

bool Snake::elementCollisionBody(int posX, int posY) const
{
	for (int i = 0; i < m_body.size(); i++) {
		/* If element is inside of the body, there is a collision */
		if ((posX == m_body[i].getPosX()) && (posY == m_body[i].getPosY()))
			return true;
	}

	/* No collision with body */
	return false;
}