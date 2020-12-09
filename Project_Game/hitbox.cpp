#include "hitbox.h"

hitbox::hitbox(Vector2f* position, Vector2f size)
{
	this->size = size;
	this->position = *position;
	box.setPosition(*position);
	box.setSize(size);
	box.setOrigin(box.getSize() / 2.f);
	box.setFillColor(Color::Transparent);
	box.setOutlineThickness(1.f);
	box.setOutlineColor(Color::Yellow);
}

void hitbox::update()
{
	box.setPosition(position);
}

void hitbox::draw(RenderWindow& window)
{
	window.draw(box);
}

bool hitbox::checkCollider(const FloatRect& frect)
{
	return this->box.getGlobalBounds().intersects(frect);
}