#pragma once

#include <SFML/Graphics.hpp>
#include "Gui.h"

class GuiRect final : Gui
{
public:
	GuiRect(sf::FloatRect dims, sf::Color fillColor,
		sf::Color outlineColor = sf::Color::Transparent);
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow* window) override;

private:
	sf::RectangleShape rect;
};