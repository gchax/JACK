#pragma once

#include "stdfn.h"
#include "collider.h"

class platform
{
public:
	platform(Texture* texture, Vector2f size, Vector2f position);

	RectangleShape body;

	void draw(RenderWindow& window);
	collider getCollider() { return collider(body); }
};