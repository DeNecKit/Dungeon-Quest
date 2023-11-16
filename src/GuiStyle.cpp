#include "GuiStyle.h"

GuiStyle::GuiStyle(
	sf::Color backgroundColor = sf::Color(48, 49, 52),
	sf::Color outlineColor = sf::Color(32, 33, 36),
	sf::Color textColor = sf::Color::Black,
	float outlineThickness)
	: backgroundColor(backgroundColor), outlineColor(outlineColor),
	  textColor(textColor), outlineThickness(outlineThickness) {}

void GuiStyle::SetCoords(sf::Vector2f pos, sf::Vector2f size)
{
	this->pos = pos;
	this->size = size;
}