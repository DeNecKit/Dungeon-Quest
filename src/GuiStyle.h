#pragma once

#include <SFML/Graphics.hpp>

class GuiStyle
{
public:
	sf::Color backgroundColor, outlineColor, textColor;
	float outlineThickness;

	GuiStyle(sf::Color backgroundColor, sf::Color outlineColor,
		sf::Color textColor, float outlineThickness = 1.f);
};