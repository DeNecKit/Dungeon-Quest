#pragma once

#include <SFML/Graphics.hpp>

class GuiRect
{
public:
	GuiRect(sf::FloatRect dims, sf::Color fillColor,
		sf::Color outlineColor = sf::Color::Transparent);
	void Render(sf::RenderWindow* window);

private:
	sf::RectangleShape rect;
};