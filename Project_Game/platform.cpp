#include "platform.h"

platform::platform(Texture* texture, Vector2f size, Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

void platform::draw(RenderWindow& window)
{
	window.draw(body);
}