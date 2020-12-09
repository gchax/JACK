#pragma once

#include "stdfn.h"

class animation
{
public:
	animation(Texture* texture, Vector2u imageCount, float switchTime);

	void update(int row, float deltaTime);

	IntRect uvRect;

private:
	Vector2u imageCount;
	Vector2u currentImage;

	float totalTime;
	float switchTime;
};
