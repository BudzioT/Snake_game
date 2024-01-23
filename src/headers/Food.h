#pragma once
#include "Texture.h"

class Food
{
public:
	Food(Texture* texture, int startPosX = 0, int startPosY = 0, int width = 0, int height = 0);
	~Food();

	/* Set width*/
	void setWidth(int width);
	/* Set height */
	void setHeight(int height);

	/* Get width */
	int getWidth() const;
	/* Get height */
	int getHeight() const;

	/* Get X axis position */
	int getPosX() const;
	/* Get Y axis position */
	int getPosY() const;

	/* Set texture */
	void setTexture(Texture* texture);

	/* Change position to the given arguments */
	void changePosition(int posX, int posY);

	/* Render food */
	void render(SDL_Rect* clip = nullptr);

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