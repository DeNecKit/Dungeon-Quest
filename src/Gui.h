#pragma once

#include "GuiStyle.h"
#include <SFML/Graphics.hpp>

class Gui
{
public:
	Gui(sf::Vector2f pos, sf::Vector2f size, GuiStyle style, bool enabled = true);
	virtual ~Gui();
	virtual void ProcessEvent(const sf::Event &) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderWindow*) = 0;

protected:
	bool IsMouseOver();

private:
	sf::Vector2f pos, size;
	bool isEnabled, needsRefresh;
};