#include "bitmap.h"

bitmap::bitmap(Texture* texture, Vector2f position, Vector2f size)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

void bitmap::draw(RenderWindow& window)
{
	window.draw(body);
}