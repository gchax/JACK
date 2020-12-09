#include "projectile.h"

projectile::projectile(Texture* texture, float speed, int attackDamage) :
	animation(texture, Vector2u(1, 4), 0.5f)
{
	this->speed = speed;
	this->damage = attackDamage;
	body.setSize(Vector2f(50.f, 50.f));
	body.setPosition(Vector2f(0.f, 0.f));
	body.setOrigin(body.getSize() / 2.f);
	body.setTexture(texture);
}

void projectile::update(float deltaTime)
{
	if (direction == UP)
	{
		row = 0;
		body.move(0, -(speed * deltaTime));
	}
	if (direction == DOWN)
	{
		row = 1;
		body.move(0, speed * deltaTime);
	}
	if (direction == LEFT)
	{
		row = 2;
		body.move(-(speed * deltaTime), 0);
	}
	if (direction == RIGHT)
	{
		row = 3;
		body.move(speed * deltaTime, 0);
	}

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void projectile::draw(RenderWindow& window)
{
	window.draw(body);
}