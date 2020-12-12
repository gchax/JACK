#include "player.h"

player::player(Texture* texture, Vector2u imageCount, float switchTime, float speed, Vector2f size) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->size = size;
	row = 2;

	body.setSize(size);
	body.setOrigin(body.getSize() / 2.f);
	body.setTexture(texture);
}

void player::update(float deltaTime)
{
	body.setFillColor(Color(255, 255, 255, 255));
	Vector2f movement(0.0f, 0.0f);

	//walk;
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		movement.y -= speed * deltaTime;
		direction = UP;
		run = false;
		row = 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		movement.y += speed * deltaTime;
		direction = DOWN;
		run = false;
		row = 3;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		movement.x -= speed * deltaTime;
		direction = LEFT;
		run = false;
		row = 5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		movement.x += speed * deltaTime;
		direction = RIGHT;
		run = false;
		row = 7;
	}

	//run;
	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::LShift))
	{
		movement.y -= speed * deltaTime / 3.f;
		direction = UP;
		run = true;
		row = 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::LShift))
	{
		movement.y += speed * deltaTime / 3.f;
		direction = DOWN;
		run = true;
		row = 3;
	}
	if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::LShift))
	{
		movement.x -= speed * deltaTime / 3.f;
		direction = LEFT;
		run = true;
		row = 5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::LShift))
	{
		movement.x += speed * deltaTime / 3.f;
		direction = RIGHT;
		run = true;
		row = 7;
	}

	if (row == 1 && movement.y == 0)
	{
		run = false;
		row = 0;
	}
	if (row == 3 && movement.y == 0)
	{
		run = false;
		row = 2;
	}
	if (row == 5 && movement.x == 0)
	{
		run = false;
		row = 4;
	}
	if (row == 7 && movement.x == 0)
	{
		run = false; 
		row = 6;
	}

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void player::updateBossFight(float deltaTime)
{
	body.setFillColor(Color(255, 255, 255, 255));
	velocity.x *= 0.f;
	velocity.y += gravity * deltaTime;

	if (Keyboard::isKeyPressed(Keyboard::W) && canJump)
	{
		canJump = false;
		velocity.y = -sqrtf(2.f * gravity * jumpHeight);
	}
	else if (Keyboard::isKeyPressed(Keyboard::S)) direction = DOWN;
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		velocity.x -= speed;
		direction = LEFT;
		run = false;
		row = 5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		velocity.x += speed;
		direction = RIGHT;
		run = false;
		row = 7;
	}
	if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::LShift))
	{
		velocity.x -= speed / 3.f;
		direction = LEFT;
		run = false;
		row = 5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::LShift))
	{
		velocity.x += speed / 3.f;
		direction = RIGHT;
		run = false;
		row = 7;
	}

	if (row == 5 && velocity.x == 0) row = 4;
	if (row == 7 && velocity.x == 0) row = 6;

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void player::updateTutorial1(float deltaTime)
{
	if (Keyboard::isKeyPressed(Keyboard::W)) row = 1;
	if (Keyboard::isKeyPressed(Keyboard::S)) row = 3;
	if (Keyboard::isKeyPressed(Keyboard::A)) row = 5;
	if (Keyboard::isKeyPressed(Keyboard::D)) row = 7;

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void player::updateTutorial2(float deltaTime)
{
	if (Keyboard::isKeyPressed(Keyboard::Space)) row = 1;
	else row = 0;

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void player::hurt()
{
	body.setFillColor(Color(255, 0, 0, 255));
}

void player::draw(RenderWindow& window)
{
	window.draw(body);
}

void player::onCollision(Vector2f direction)
{
	if (direction.x < 0.f) velocity.x = 0.f;
	else if (direction.x > 0.f) velocity.x = 0.f;
	if (direction.y < 0.f)
	{
		velocity.y = 0.f;
		canJump = true;
	}
	else if (direction.y > 0.f) velocity.y = 0.f;
}