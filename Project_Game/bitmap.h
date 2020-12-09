#pragma once

#include "stdfn.h"
#include "collider.h"

class bitmap
{
public:
	bitmap(Texture* texture, Vector2f position, Vector2f size);

	void setFillColor(const Color& x) { return body.setFillColor(x); }
	void draw(RenderWindow& window);
	collider getCollider() { return collider(body); }
	FloatRect getGlobalBounds() { return body.getGlobalBounds(); }

private:
	RectangleShape body;
};