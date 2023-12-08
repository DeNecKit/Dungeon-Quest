#pragma once

#include <SFML/Graphics.hpp>

class GuiDraggable
{
public:
	GuiDraggable(sf::Time holdTime);
	void Update(sf::Time deltaTime);
	bool ShouldDrag();
	void Reset();

private:
	const sf::Time holdTime;
	sf::Time passedTime;
};