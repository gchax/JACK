#include "button.h"

button::button(Vector2f position, Vector2f shapeSize, Color shapeIdleColor, Color shapeHoverColor, Color shapeActiveColor,
	float originDenomenator, Font* font, float fontSize, string text, Color textIdleColor, Color textHoverColor, Color textActiveColor)
{
	this->buttonState = BTN_IDLE;
	this->shapeIdleColor = shapeIdleColor;
	this->shapeHoverColor = shapeHoverColor;
	this->shapeActiveColor = shapeActiveColor;
	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;

	this->shape.setPosition(position);
	this->shape.setSize(shapeSize);
	this->shape.setOrigin(shape.getSize() / originDenomenator);
	this->shape.setFillColor(this->shapeIdleColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(this->textIdleColor);
	this->text.setCharacterSize(fontSize);
	this->text.setPosition(this->shape.getPosition());
	this->text.setOrigin(this->text.getLocalBounds().width / originDenomenator, this->text.getLocalBounds().height / originDenomenator);
}

void button::update(const Vector2f mousePos)
{
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->shapeIdleColor);
		this->text.setFillColor(this->textIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->shapeHoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->shapeActiveColor);
		this->text.setFillColor(this->textActiveColor);
		break;

	default:
		this->shape.setFillColor(Color::Red);
		this->text.setFillColor(Color::Green);
		break;
	}
}

void button::draw(RenderWindow& window)
{
	window.draw(this->shape);
	window.draw(this->text);
}
