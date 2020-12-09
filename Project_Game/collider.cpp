#include "collider.h"

collider::collider(RectangleShape& body) :
	body(body) {}

bool collider::checkCollider(collider other, float push)
{
	Vector2f otherPosition = other.getPosition();
	Vector2f otherHalfSize = other.getHalfSize();
	Vector2f thisPosition = getPosition();
	Vector2f thisHalfSize = getHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = min(max(push, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				move(intersectX * (1.0f - push), 0.0f);
				other.move(-intersectX * push, 0.0f);
			}
			else
			{
				move(-intersectX * (1.0f - push), 0.0f);
				other.move(intersectX * push, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				move(0.0f, intersectY * (1.0f - push));
				other.move(0.0f, -intersectY * push);
			}
			else
			{
				move(0.0f, -intersectY * (1.0f - push));
				other.move(0.0f, intersectY * push);
			}
		}
		return true;
	}
	return false;
}

bool collider::checkGroundCollision(collider other, Vector2f& direction, float push)
{
	Vector2f otherPosition = other.getPosition();
	Vector2f otherHalfSize = other.getHalfSize();
	Vector2f thisPosition = getPosition();
	Vector2f thisHalfSize = getHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = min(max(push, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				move(intersectX * (1.0f - push), 0.0f);
				other.move(-intersectX * push, 0.0f);

				direction.x = 1;
				direction.y = 0;
			}
			else
			{
				move(-intersectX * (1.0f - push), 0.0f);
				other.move(intersectX * push, 0.0f);

				direction.x = -1;
				direction.y = 0;
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				move(0.0f, intersectY * (1.0f - push));
				other.move(0.0f, -intersectY * push);

				direction.x = 0;
				direction.y = 1;
			}
			else
			{
				move(0.0f, -intersectY * (1.0f - push));
				other.move(0.0f, intersectY * push);

				direction.x = 0;
				direction.y = -1;
			}
		}
		return true;
	}
	return false;
}
