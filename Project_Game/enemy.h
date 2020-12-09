#pragma once

#include "stdfn.h"
#include "animation.h"
#include "collider.h"

class enemy
{
public:
	int direction = LEFT;
	int counter = 0;
	bool isCollided = false;
	bool isDead = false;
	bool isRespawned = false;
	bool isSpawned[15] = { true,true,true,true,true,true,true,true,true,true,true,true,true,true,true };
	bool isAggroed = false;
	bool shoot = false;
	int action = 0;
	int effectLifetime = 0;
	float hp;
	float damage;
	float speed;
	RectangleShape body;
	enemy(Texture* texture, Vector2u imageCount, Vector2f size, Vector2f position, float switchTime, float speed, float hp, int damage);

	void updateStill(float deltaTime);
	void updateFly(float deltaTime);
	void updateAggroedFly(float deltaTime, Vector2f playerPosition);
	void updateWalk(float deltaTime);
	void updateAggrovated(float deltaTime, Vector2f playerPosition);
	void updateBoss(float deltaTime, int bossPhase);
	void draw(RenderWindow& window);

	collider getCollider() { return collider(body); }

private:
	animation animation;
	Vector2f size;
	Vector2f position;
	unsigned int row = 0;
	int bossPhase = IDLE;
};