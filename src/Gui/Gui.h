#pragma once

#include <SFML/Graphics.hpp>

class Gui
{
public:
	Gui(sf::FloatRect dims);
	virtual ~Gui();
	virtual void ProcessEvent(const sf::Event &) = 0;
	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Render(sf::RenderWindow*) = 0;
	bool IsMouseOver();

	static inline sf::Color
		ButtonFillColor = sf::Color(78, 74, 78),
		ButtonOutlineColor = sf::Color(68, 36, 52),
		ItemSlotFillColor = sf::Color(68, 36, 52),
		ItemSlotOutlineColor = sf::Color(133, 76, 48);

protected:
	sf::FloatRect dimensions;
};