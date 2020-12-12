#pragma once

#include "stdfn.h"
#include "animation.h"
#include "collider.h"
#include "projectile.h"
#include "playerGUI.h"

class player
{
public:
	player(Texture* texture, Vector2u imageCount, float switchTime, float speed, Vector2f size);

	RectangleShape body;
	int direction = IDLE;
	float speed = 0.f;
	float hp = 0.f;
	float mp = 0.f;
	float gravity = 0.f;
	int money = 0;
	bool run = false;

	void update(float deltaTime);
	void updateBossFight(float deltaTime);
	void updateTutorial1(float deltaTime);
	void updateTutorial2(float deltaTime);
	void hurt();
	void draw(RenderWindow& window);
	void onCollision(Vector2f direction);
	void setAnimationRow(unsigned int r) { row = r; }
	
	collider getCollider() { return collider(body); }

private:
	animation animation;
	unsigned int row;
	Vector2f velocity;
	Vector2f size;
	bool canJump = false;
	float jumpHeight = 200.f;
};