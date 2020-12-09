#pragma once

#include "stdfn.h"
#include "animation.h"
#include "collider.h"

class projectile
{
public:
	projectile(Texture* texture, float speed, int damage);

	int direction = IDLE;
	bool isCollided = false;
	float speed;
	float damage;
	RectangleShape body;

	void update(float deltaTime);
	void draw(RenderWindow& window);

	collider getCollider() { return collider(body); }

private:
	animation animation;
	unsigned int row = 0;
};