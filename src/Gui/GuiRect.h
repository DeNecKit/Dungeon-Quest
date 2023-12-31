#pragma once

#include <SFML/Graphics.hpp>
#include "Gui.h"

class GuiRect final : public Gui
{
public:
	GuiRect(sf::FloatRect dims, sf::Color fillColor,
		sf::Color outlineColor = sf::Color::Transparent);
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow *window) override;
	void ScaleSize(sf::Vector2f factors);
	void SetDimensions(sf::FloatRect dims);

private:
	sf::RectangleShape rect;
};