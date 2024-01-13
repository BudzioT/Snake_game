#pragma once
#include "Texture.h"

class SnakeSegment
{
public:
	SnakeSegment(int posX = 0, int posY = 0, double angle = 0.0);
	~SnakeSegment();

	/* Render segment */
	void render(SDL_Rect* clip);

	/* Get X position value */
	int getPosX() const;
	/* Get Y position value */
	int getPosY() const;
	/* Get reference to X position */
	int& posX();
	/* Get reference to Y position */
	int& posY();

	/* Get angle value */
	double getAngle() const;

	/* Set width */
	void setWidth(int width);
	/* Set height */
	void setHeight(int height);

	/* Get width */
	int getWidth() const;
	/* Get height */
	int getHeight() const;

	/* Set this segment as head */
	void setHead(bool flag);
	/* Set this segment as tail */
	void setTail(bool flag);

	/* Set angle */
	void setAngle(double angle);
	/* Set position */
	void setPosition(int posX, int posY);

	/* Is this segment a head */
	bool isThisHead() const;
	/* Is this segment a tail */
	bool isThisTail() const;

	/* Set texture */
	void setTexture(Texture* texture);

private:
	/* Universal width */
	static int m_width;
	/* Universal height */
	static int m_height;

	/* Position on the X axis */
	int m_posX;
	/* Position on the Y axis */
	int m_posY;

	/* Angle in which segment is turned */
	double m_angle;

	/* Segment head flag */
	bool m_head;
	/*  Segment tail flag */
	bool m_tail;

	/* Universal texture */
	static Texture* m_texture;
};