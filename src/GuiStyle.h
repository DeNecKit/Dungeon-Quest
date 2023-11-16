#pragma once

#include <SFML/Graphics.hpp>

class GuiStyle
{
public:
	sf::Vector2f pos, size;
	sf::Color backgroundColor, outlineColor, textColor;
	float outlineThickness;

	GuiStyle(sf::Color backgroundColor, sf::Color outlineColor,
		sf::Color textColor, float outlineThickness = 1.f);
	void SetCoords(sf::Vector2f pos, sf::Vector2f size);
};