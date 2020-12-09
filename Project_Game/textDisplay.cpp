#include "textDisplay.h"

textDisplay::textDisplay(Color textColor)
{
	text.setFillColor(textColor);
	text.setCharacterSize(25);
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
}

void textDisplay::update(float deltaTime)
{
	text.move(0.f, -speed * deltaTime);
	counter++;
	if (counter >= lifetime) destroy = true;
}