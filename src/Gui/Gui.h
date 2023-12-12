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

	sf::FloatRect dimensions;

	static inline sf::Color
		TextColor = sf::Color(222, 238, 214),
		ShadowColor = sf::Color(133, 149, 161),
		ButtonFillColor = sf::Color(133, 76, 48),
		ButtonOutlineColor = sf::Color(210, 125, 44),
		MenuFillColor = sf::Color(103, 46, 18),
		MenuOutlineColor = sf::Color(218, 212, 94),
		ItemSlotFillColor = sf::Color(68, 36, 52),
		ItemSlotOutlineColor = MenuOutlineColor,
		HealthBarFillColor = sf::Color(139, 0, 0);
};