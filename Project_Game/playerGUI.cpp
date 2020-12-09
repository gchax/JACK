#include "playerGUI.h"

playerGUI::playerGUI(Font* font, Texture* HPP, Texture* MPP, float playerHP, float maxHP, float playerMP, float maxMP, int hpp, int mpp,
	int playerMoney, int score, int playerWandLevel, int key, float bossHP)
{
	this->font = font;
	this->hp = playerHP;
	this->intHP = this->hp;
	this->maxHP = maxHP;
	this->intMaxHP = this->maxHP;
	this->mp = playerMP;
	this->intMP = this->mp;
	this->maxMP = maxMP;
	this->intMaxMP = this->maxMP;
	this->hpp = hpp;
	this->mpp = mpp;
	this->wand = playerWandLevel;
	this->money = playerMoney;
	this->score = score;
	this->key = key;
	this->bossHP = bossHP;
	this->intBossHP = this->bossHP;

	this->hpBarBase.setSize(Vector2f(barMaxWidth, 40.f));
	this->hpBarBase.setFillColor(Color(50, 50, 50));
	this->hpBarBase.setOutlineColor(Color::Black);
	this->hpBarBase.setOutlineThickness(3);

	this->hpAmount.setSize(Vector2f(barMaxWidth, 40.f));
	this->hpAmount.setFillColor(Color::Green);
	this->hpAmount.setOutlineColor(Color::Black);
	this->hpAmount.setOutlineThickness(3);

	this->hpRead.setCharacterSize(15);
	this->hpRead.setFont(*this->font);
	this->hpRead.setString(to_string(intHP) + " / " + to_string(intMaxHP));
	this->hpRead.setFillColor(Color::White);
	this->hpRead.setOutlineThickness(1);

	this->mpBarBase.setSize(Vector2f(barMaxWidth, 15.f));
	this->mpBarBase.setFillColor(Color(50, 50, 50));
	this->mpBarBase.setOutlineColor(Color::Black);
	this->mpBarBase.setOutlineThickness(3);

	this->mpAmount.setSize(Vector2f(barMaxWidth, 15.f));
	this->mpAmount.setFillColor(Color::Magenta);
	this->mpAmount.setOutlineColor(Color::Black);
	this->mpAmount.setOutlineThickness(3);

	this->mpRead.setCharacterSize(15);
	this->mpRead.setFont(*this->font);
	this->mpRead.setString(to_string(intMP) + " / " + to_string(intMaxMP));
	this->mpRead.setFillColor(Color::White);
	this->mpRead.setOutlineThickness(1);

	this->hpP.setSize(Vector2f(60.f, 60.f));
	this->hpP.setTexture(HPP);

	this->mpP.setSize(Vector2f(60.f, 60.f));
	this->mpP.setTexture(MPP);

	this->hppCounter.setCharacterSize(15);
	this->hppCounter.setFont(*this->font);
	this->hppCounter.setString(to_string(this->hpp));
	this->hppCounter.setFillColor(Color::White);
	this->hppCounter.setOutlineThickness(2);

	this->mppCounter.setCharacterSize(15);
	this->mppCounter.setFont(*this->font);
	this->mppCounter.setString(to_string(this->mpp));
	this->mppCounter.setFillColor(Color::White);
	this->mppCounter.setOutlineThickness(2);

	this->Score.setCharacterSize(30);
	this->Score.setFont(*this->font);
	this->Score.setString("SCORE: " + to_string(this->score));
	this->Score.setFillColor(Color::White);
	this->Score.setOutlineThickness(2);

	this->Money.setCharacterSize(30);
	this->Money.setFont(*this->font);
	this->Money.setString("COINS: " + to_string(this->money));
	this->Money.setFillColor(Color::White);
	this->Money.setOutlineThickness(2);

	this->wandLevel.setCharacterSize(20);
	this->wandLevel.setFont(*this->font);
	this->wandLevel.setFillColor(Color::White);
	this->wandLevel.setOutlineThickness(2);

	this->Key.setCharacterSize(20);
	this->Key.setFont(*this->font);
	this->Key.setFillColor(Color::White);
	this->Key.setOutlineThickness(2);

	this->bossHpBarBase.setSize(Vector2f(bossBarMaxWidth, 60.f));
	this->bossHpBarBase.setFillColor(Color(50, 50, 50));
	this->bossHpBarBase.setOutlineColor(Color::Black);
	this->bossHpBarBase.setOutlineThickness(4);

	this->bossHpAmount.setSize(Vector2f(bossBarMaxWidth, 60.f));
	this->bossHpAmount.setFillColor(Color::Red);
	this->bossHpAmount.setOutlineColor(Color::Black);
	this->bossHpAmount.setOutlineThickness(4);

	this->bossHpRead.setCharacterSize(20);
	this->bossHpRead.setFont(*this->font);
	this->bossHpRead.setString(to_string(intBossHP) + " / " + to_string(200000));
	this->bossHpRead.setFillColor(Color::White);
	this->bossHpRead.setOutlineThickness(1);
}

void playerGUI::updateStatus(float deltaTime, Vector2f windowSize, Vector2f playerPosition)
{
	if (this->intHP <= 0) this->intHP = 0;
	if (this->intMP <= 0) this->intMP = 0;

	float hpPercentage = hp / maxHP;
	float hpDisplay = static_cast<float>(std::floor(this->barMaxWidth * hpPercentage));
	if (hpDisplay < 0) hpDisplay = 0;
	this->hpAmount.setSize((Vector2f(hpDisplay, this->hpAmount.getSize().y)));

	float mpPercentage = mp / maxMP;
	float mpDisplay = static_cast<float>(std::floor(this->barMaxWidth * mpPercentage));
	if (mpDisplay < 0) mpDisplay = 0;
	this->mpAmount.setSize((Vector2f(mpDisplay, this->mpAmount.getSize().y)));

	string keycount;
	if (key == 0) keycount = "";
	else if (key > 0 && key < 5) keycount = "KEY: " + to_string(this->key);
	else if (key == 5) keycount = "CASTLE DOOR UNLOCKED";

	this->hpBarBase.setPosition(playerPosition.x - windowSize.x / 2.f + 20.f, playerPosition.y - windowSize.y / 2.f + 20.f);
	this->hpAmount.setPosition(this->hpBarBase.getPosition());
	this->hpRead.setOrigin(Vector2f(0.f, hpRead.getGlobalBounds().height / 2.f));
	this->hpRead.setPosition(this->hpBarBase.getPosition().x + this->hpBarBase.getSize().x + 10.f, this->hpBarBase.getPosition().y + this->hpBarBase.getSize().y / 2.f);

	this->mpBarBase.setPosition(playerPosition.x - windowSize.x / 2.f + 20.f, playerPosition.y - windowSize.y / 2.f + 80.f);
	this->mpAmount.setPosition(this->mpBarBase.getPosition());
	this->mpRead.setOrigin(Vector2f(0.f, mpRead.getGlobalBounds().height / 2.f));
	this->mpRead.setPosition(this->mpBarBase.getPosition().x + this->mpBarBase.getSize().x + 10.f, this->mpBarBase.getPosition().y + this->mpBarBase.getSize().y / 2.f);

	this->Score.setOrigin(this->Score.getLocalBounds().width / 2.f, 0.f);
	this->Score.setPosition(playerPosition.x, playerPosition.y - windowSize.y / 2.f + 20.f);

	this->hpP.setPosition(playerPosition.x - windowSize.x / 2.f + 20.f, playerPosition.y - windowSize.y / 2.f + 115.f);
	this->hppCounter.setPosition(this->hpP.getPosition().x + hpP.getSize().x - hppCounter.getGlobalBounds().width, this->hpP.getPosition().y + hpP.getSize().y - hppCounter.getGlobalBounds().height);

	this->mpP.setPosition(playerPosition.x - windowSize.x / 2.f + 100.f, playerPosition.y - windowSize.y / 2.f + 115.f);
	this->mppCounter.setPosition(this->mpP.getPosition().x + mpP.getSize().x - mppCounter.getGlobalBounds().width, this->mpP.getPosition().y + mpP.getSize().y - mppCounter.getGlobalBounds().height);

	this->Key.setString(keycount);
	this->Key.setOrigin(this->Key.getLocalBounds().width, 0.f);
	this->Key.setPosition(playerPosition.x + windowSize.x / 2.f - 20.f, playerPosition.y - windowSize.y / 2.f + 105.f);
}

void playerGUI::updateCoin(float deltaTime, Vector2f windowSize, Vector2f playerPosition)
{
	this->Money.setOrigin(this->Money.getLocalBounds().width, 0.f);
	this->Money.setPosition(playerPosition.x + windowSize.x / 2.f - 20.f, playerPosition.y - windowSize.y / 2.f + 20.f);
}

void playerGUI::updateWandState(float deltaTime, Vector2f windowSize, Vector2f playerPosition)
{
	string state;
	if (wand == 0) state = "";
	else if (wand > 0 && wand < 60) state = "WAND LEVEL: " + to_string(this->wand);
	else if (wand == 60) state = "WAND LEVEL: MAX";

	this->wandLevel.setString(state);
	this->wandLevel.setOrigin(this->wandLevel.getLocalBounds().width, 0.f);
	this->wandLevel.setPosition(playerPosition.x + windowSize.x / 2.f - 20.f, playerPosition.y - windowSize.y / 2.f + 70.f);
}

void playerGUI::updateCastle(float deltaTime, Vector2f windowSize)
{
	if (this->intHP <= 0) this->intHP = 0;
	if (this->intMP <= 0) this->intMP = 0;
	if (this->intBossHP <= 0) this->intBossHP = 0;

	float hpPercentage = hp / maxHP;
	float hpDisplay = static_cast<float>(std::floor(this->barMaxWidth * hpPercentage));
	if (hpDisplay < 0) hpDisplay = 0;
	this->hpAmount.setSize((Vector2f(hpDisplay, this->hpAmount.getSize().y)));

	float mpPercentage = mp / maxMP;
	float mpDisplay = static_cast<float>(std::floor(this->barMaxWidth * mpPercentage));
	if (mpDisplay < 0) mpDisplay = 0;
	this->mpAmount.setSize((Vector2f(mpDisplay, this->mpAmount.getSize().y)));

	float bossHpPercentage = bossHP / 200000;
	float bossHpDisplay = static_cast<float>(std::floor(this->bossBarMaxWidth * bossHpPercentage));
	if (bossHpDisplay < 0) bossHpDisplay = 0;
	this->bossHpAmount.setSize((Vector2f(bossHpDisplay, this->bossHpAmount.getSize().y)));

	string state;
	if (wand == 0) state = "";
	else if (wand > 0 && wand < 60) state = "WAND LEVEL: " + to_string(this->wand);
	else if (wand == 60) state = "WAND LEVEL: MAX";

	this->hpBarBase.setOrigin(hpBarBase.getSize().x, 0.f);
	this->hpBarBase.setPosition(windowSize.x / 2.f - 20.f, 20.f - windowSize.y / 2.f);
	this->hpAmount.setOrigin(hpAmount.getSize().x, 0.f);
	this->hpAmount.setPosition(this->hpBarBase.getPosition());
	this->hpRead.setOrigin(hpRead.getGlobalBounds().width, hpRead.getGlobalBounds().height / 2.f);
	this->hpRead.setPosition(this->hpBarBase.getPosition().x - this->hpBarBase.getSize().x - 10.f, this->hpBarBase.getPosition().y + this->hpBarBase.getSize().y / 2.f);

	this->mpBarBase.setOrigin(mpBarBase.getSize().x, 0.f);
	this->mpBarBase.setPosition(windowSize.x / 2.f - 20.f, 80.f - windowSize.y / 2.f);
	this->mpAmount.setOrigin(mpAmount.getSize().x, 0.f);
	this->mpAmount.setPosition(this->mpBarBase.getPosition());
	this->mpRead.setOrigin(mpRead.getGlobalBounds().width, mpRead.getGlobalBounds().height / 2.f);
	this->mpRead.setPosition(this->mpBarBase.getPosition().x - this->mpBarBase.getSize().x - 10.f, this->mpBarBase.getPosition().y + this->mpBarBase.getSize().y / 2.f);

	this->bossHpBarBase.setPosition(20.f - windowSize.x / 2.f, 20.f - windowSize.y / 2.f);
	this->bossHpAmount.setPosition(this->bossHpBarBase.getPosition());
	this->bossHpRead.setOrigin(0.f, bossHpRead.getGlobalBounds().height / 2.f);
	this->bossHpRead.setPosition(this->bossHpBarBase.getPosition().x + this->bossHpBarBase.getSize().x + 20.f, this->bossHpBarBase.getPosition().y + this->bossHpBarBase.getSize().y / 2.f);

	this->Score.setPosition(20.f - windowSize.x / 2.f, 110.f - windowSize.y / 2.f);

	this->hpP.setOrigin(hpP.getSize().x, 0.f);
	this->hpP.setPosition(windowSize.x / 2.f - 100.f, 115.f - windowSize.y / 2.f);
	this->hppCounter.setPosition(this->hpP.getPosition().x - hppCounter.getGlobalBounds().width, this->hpP.getPosition().y + hpP.getSize().y - hppCounter.getGlobalBounds().height);

	this->mpP.setOrigin(mpP.getSize().x, 0.f);
	this->mpP.setPosition(windowSize.x / 2.f - 20.f, 115.f - windowSize.y / 2.f);
	this->mppCounter.setPosition(this->mpP.getPosition().x - mppCounter.getGlobalBounds().width, this->mpP.getPosition().y + mpP.getSize().y - mppCounter.getGlobalBounds().height);

	this->Money.setFillColor(Color(255, 255, 255, 0));
	this->Money.setOutlineThickness(0);
	this->Money.setOrigin(this->Money.getLocalBounds().width, 0.f);
	this->Money.setPosition(0.f, 0.f);

	this->wandLevel.setString(state);
	this->wandLevel.setOrigin(this->wandLevel.getLocalBounds().width, 0.f);
	this->wandLevel.setPosition(this->hpP.getPosition().x - this->hpP.getSize().x - 20.f, 135.f - windowSize.y / 2.f);
}

void playerGUI::drawStatus(RenderWindow& window)
{
	window.draw(this->hpBarBase);
	window.draw(this->hpAmount);
	window.draw(this->hpRead);
	window.draw(this->mpBarBase);
	window.draw(this->mpAmount);
	window.draw(this->mpRead);
	window.draw(this->Score);
	window.draw(this->hpP);
	window.draw(this->hppCounter);
	window.draw(this->mpP);
	window.draw(this->mppCounter);
	window.draw(this->Key);
}

void playerGUI::drawWandState(RenderWindow& window)
{
	window.draw(this->wandLevel);
}

void playerGUI::drawCoin(RenderWindow& window)
{
	window.draw(this->Money);
}

void playerGUI::drawBossHpBar(RenderWindow& window)
{
	window.draw(this->bossHpBarBase);
	window.draw(this->bossHpAmount);
	window.draw(this->bossHpRead);
}