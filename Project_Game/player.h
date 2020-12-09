#pragma once

#include "stdfn.h"
#include "animation.h"
#include "collider.h"
#include "projectile.h"
#include "playerGUI.h"
#include "hitbox.h"

class player
{
public:
	player(Texture* texture, Vector2u imageCount, float switchTime, float speed);

	RectangleShape body;
	int direction = IDLE;
	float speed = 0.f;
	float hp = 0.f;
	float mp = 0.f;
	int money = 0;
	float gravity = 0.f;

	void update(float deltaTime);
	void updateBossFight(float deltaTime);
	void hurt();
	void draw(RenderWindow& window);
	void onCollision(Vector2f direction);
	void setAnimationRow(unsigned int r) { row = r; }
	
	collider getCollider() { return collider(body); }

private:
	animation animation;
	unsigned int row;
	Vector2f velocity;
	bool canJump = false;
	float jumpHeight = 200.f;
};