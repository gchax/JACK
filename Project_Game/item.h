#pragma once

#include "stdfn.h"
#include "animation.h"
#include "collider.h"

class item
{
public:
	bool isPickedUp = false;
	bool destroy = false;
	int lifetime = 0;
	float gravity = 0.f;
	RectangleShape body;

	item(Texture* texture, Vector2u imageCount, Vector2f size);
	void update(float deltaTime);
	void updateGravity(float deltaTime);
	void onCollision(Vector2f direction);
	void draw(RenderWindow& window);

	collider getCollider() { return collider(body); }

private:
	animation animation;
	Vector2f size;
	Vector2f velocity;
};