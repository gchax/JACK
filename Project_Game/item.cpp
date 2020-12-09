#include "item.h"

item::item(Texture* texture, Vector2u imageCount, Vector2f size) :
	animation(texture, imageCount, 0.05f)
{
	this->size = size;

	body.setSize(size);
	body.setOrigin(body.getSize() / 2.f);
	body.setTexture(texture);
}

void item::update(float deltaTime)
{
	animation.update(0, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void item::updateGravity(float deltaTime)
{
	velocity.x *= 0.f;
	velocity.y += gravity * deltaTime;

	animation.update(0, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void item::onCollision(Vector2f direction)
{
	if (direction.x < 0.f) velocity.x = 0.f;
	else if (direction.x > 0.f) velocity.x = 0.f;
	if (direction.y < 0.f) velocity.y = 0.f;
	else if (direction.y > 0.f) velocity.y = 0.f;
}

void item::draw(RenderWindow& window)
{
	window.draw(body);
}