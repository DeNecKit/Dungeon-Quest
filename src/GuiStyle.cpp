#include "GuiStyle.h"

GuiStyle::GuiStyle(
	sf::Color backgroundColor = sf::Color(48, 49, 52),
	sf::Color outlineColor = sf::Color(32, 33, 36),
	sf::Color textColor = sf::Color::Black,
	float outlineThickness)
	: backgroundColor(backgroundColor), outlineColor(outlineColor),
	  textColor(textColor), outlineThickness(outlineThickness) {}