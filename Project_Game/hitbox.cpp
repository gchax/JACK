#include "hitbox.h"

hitbox::hitbox(Vector2f* position, Vector2f size)
{
	this->position = *position;
	box.setPosition(this->position);
	box.setSize(size);
	box.setOrigin(box.getSize() / 2.f);
	box.setFillColor(Color::Transparent);
	box.setOutlineThickness(1.f);
	box.setOutlineColor(Color::Yellow);
}

void hitbox::update()
{
	box.setPosition(this->position);
}

void hitbox::draw(RenderWindow& window)
{
	window.draw(box);
}