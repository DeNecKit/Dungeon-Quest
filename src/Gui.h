#pragma once

#include "GuiStyle.h"
#include <SFML/Graphics.hpp>

class Gui
{
public:
	Gui(sf::FloatRect dimensions);
	virtual void ProcessEvent(const sf::Event &) = 0;
	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Render(sf::RenderWindow*) = 0;

	bool IsEnabled;

protected:
	bool IsMouseOver();
	sf::FloatRect dimensions;
};