#pragma once

#include <SFML/Graphics.hpp>

class Gui
{
public:
	Gui(sf::FloatRect dims);
	virtual void ProcessEvent(const sf::Event &) = 0;
	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Render(sf::RenderWindow*) = 0;

protected:
	bool IsMouseOver();
	sf::FloatRect dimensions;
};