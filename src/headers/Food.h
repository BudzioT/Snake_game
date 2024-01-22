#pragma once
#include "Texture.h"

class Food
{
public:
	Food(int startPosX = 0, int startPosY = 0);
	~Food();

	/* Set universal width*/

	/* Change position to the given arguments */
	void changePosition(int posX, int posY);

private:
	/* Universal width */
	static int m_width;
	/* Universal height */
	static int m_height;

	/* Position on the X axis */
	int m_posX;
	/* Position on the Y axis */
	int m_posY;

	/* Texture */
	static Texture* m_texture;
};