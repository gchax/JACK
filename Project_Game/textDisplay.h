#pragma once

#include "stdfn.h"

class textDisplay
{
public:
	Text text;
	int counter = 0;
	int lifetime = 50;
	float speed = 300;
	bool destroy = false;

	textDisplay(Color textColor);

	void update(float deltaTime);

private:
};