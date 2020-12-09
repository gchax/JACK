#include "enemy.h"
#include "random.h"

enemy::enemy(Texture* texture, Vector2u imageCount, Vector2f size, Vector2f position, float switchTime, float speed, float hp, int damage) :
	animation(texture, imageCount, switchTime)
{
	this->size = size;
	this->position = position;
	this->speed = speed;
	this->hp = hp;
	this->damage = damage;

	body.setSize(size);
	body.setPosition(position);
	body.setTexture(texture);
	body.setOrigin(body.getSize() / 2.f);
}

void enemy::updateStill(float deltaTime)
{
	animation.update(0, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void enemy::updateFly(float deltaTime)
{
	if (body.getPosition().x >= 0 && body.getPosition().x <= 900) row = 0;
	else row = 1;

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void enemy::updateAggroedFly(float deltaTime, Vector2f playerPosition)
{
	if (action == 1)
	{
		if (body.getPosition().y > playerPosition.y) body.move(0, -speed * deltaTime);
		else body.move(0, speed * deltaTime);
	}
	if (body.getPosition().x >= 0 && body.getPosition().x <= 900) row = 0;
	else row = 1;

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void enemy::updateWalk(float deltaTime)
{
	if (direction == IDLE);
	if (direction == UP) body.move(0, -speed * deltaTime);
	if (direction == DOWN) body.move(0, speed * deltaTime);
	if (direction == RIGHT)
	{
		body.move(speed * deltaTime, 0);
		row = 0;
	}
	if (direction == LEFT)
	{
		body.move(-speed * deltaTime, 0);
		row = 1;
	}

	counter++;
	if (counter >= 300)
	{
		direction = generateIntRandom(10, 0);
		counter = 0;
	}

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void enemy::updateAggrovated(float deltaTime, Vector2f playerPosition)
{
	if (action == 1)
	{
		if (body.getPosition().x > playerPosition.x)
		{
			body.move(-speed * deltaTime, 0);
			row = 1;
		}
		else
		{
			body.move(speed * deltaTime, 0);
			row = 0;
		}
		if (body.getPosition().y > playerPosition.y) body.move(0, -speed * deltaTime);
		else body.move(0, speed * deltaTime);
	}

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void enemy::updateBoss(float deltaTime, int bossPhase)
{
	this->bossPhase = bossPhase;
	if (bossPhase == AGGROVATED || bossPhase == INFURIATED || bossPhase == MURDEROUS) row = 1;
	else row = 0;
	if (isDead == true)
	{
		row = 2;
		effectLifetime++;
		if (effectLifetime >= 100) row = 3;
	}

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void enemy::draw(RenderWindow& window)
{
	window.draw(body);
}