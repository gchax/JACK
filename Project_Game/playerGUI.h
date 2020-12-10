#pragma once

#include "stdfn.h"
#include "player.h"

class playerGUI
{
public:
	playerGUI(Font* font, Texture* HPP, Texture* MPP, float playerHP, float maxHP, float playerMP, float maxMP, float playerEnergy, int hpp, int mpp,
		int playerMoney, int score, int playerWandLevel, int key, float bossHP);

	void updateStatus(float deltaTime, Vector2f windowSize, Vector2f playerPosition);
	void updateWandState(float deltaTime, Vector2f windowSize, Vector2f playerPosition);
	void updateCoin(float deltaTime, Vector2f windowSize, Vector2f playerPosition);
	void updateCastle(float deltaTime, Vector2f windowSize);
	void drawStatus(RenderWindow& window);
	void drawWandState(RenderWindow& window);
	void drawCoin(RenderWindow& window);
	void drawBossHpBar(RenderWindow& window);

private:
	RectangleShape hpBarBase;
	RectangleShape hpAmount;
	RectangleShape mpBarBase;
	RectangleShape mpAmount;
	RectangleShape energyBarBase;
	RectangleShape energyAmount;
	RectangleShape bossHpBarBase;
	RectangleShape bossHpAmount;
	RectangleShape hpP;
	RectangleShape mpP;
	Text hpRead;
	Text mpRead;
	Text bossHpRead;
	Text hppCounter;
	Text mppCounter;
	Text Key;
	Text wandLevel;
	Text Money;
	Text Score;
	Font* font;
	string keycount;
	string state;
	float barMaxWidth = 400.f;
	float bossBarMaxWidth = 800.f;
	float hp;
	float maxHP;
	float mp;
	float maxMP;
	float energy;
	float bossHP;
	float hpPercentage;
	float hpDisplay;
	float mpPercentage;
	float mpDisplay;
	float energyPercentage;
	float energyDisplay;
	float bossHpPercentage;
	float bossHpDisplay;
	int intHP;
	int intMP;
	int intMaxHP;
	int intMaxMP;
	int intBossHP;
	int hpp;
	int mpp;
	int key;
	int wand;
	int money;
	int score;
};
