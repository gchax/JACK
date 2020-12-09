#pragma once

#include "stdfn.h"

class collider
{
public:
	collider(RectangleShape& body);

	void move(float dx, float dy) { body.move(dx, dy); }

	bool checkCollider(collider other, float push);
	bool checkGroundCollision(collider other, Vector2f& direction, float push);
	Vector2f getPosition() { return body.getPosition(); }
	Vector2f getHalfSize() { return body.getSize() / 2.0f; }

private:
	RectangleShape& body;
};