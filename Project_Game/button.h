#pragma once

#include "stdfn.h"

class button
{
public:
	button(Vector2f position, Vector2f shapeSize, Color shapeIdleColor, Color shapeHoverColor, Color shapeActiveColor,
		float originDenomenator, Font* font, float fontSize, string text, Color textIdleColor, Color textHoverColor, Color textActiveColor);

	void update(const Vector2f mousePos);
	void draw(RenderWindow& window);
	void setOrigin(Vector2f(a)) { return shape.setOrigin(a); }
	void setTextFillColor(const Color& b) { return text.setFillColor(b); }
	void setTextOutlineColor(const Color& c) { return text.setOutlineColor(c); }
	void setTextOutlineThickness(float d) { return text.setOutlineThickness(d); }
	void setShapeFillColor(const Color& e) { return shape.setFillColor(e); }
	void setShapeOutlineColor(const Color& f) { return shape.setOutlineColor(f); }
	void setShapeOutlineThickness(float g) { return shape.setOutlineThickness(g); }
	void setPosition(Vector2f(h)) { return shape.setPosition(h); }
	void move(Vector2f(i)) { return shape.move(i); }

	FloatRect getGlobalBounds() { return shape.getGlobalBounds(); }
	Vector2f getSize() { return shape.getSize(); }
	Vector2f getPosition() { return shape.getPosition(); }
	RectangleShape shape;
	Text text;

private:
	short unsigned buttonState;

	Font* font;

	Color shapeIdleColor;
	Color shapeHoverColor;
	Color shapeActiveColor;
	Color textIdleColor;
	Color textHoverColor;
	Color textActiveColor;
};