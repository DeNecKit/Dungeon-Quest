#pragma once

#include "Gui.h"

class GuiText final : public Gui
{
public:
	GuiText(sf::FloatRect dims, const sf::String &str,
		sf::Font* font, unsigned int chSize, sf::Color textColor,
		sf::Color shadowColor = sf::Color::Transparent);
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;

private:
	sf::FloatRect innerDimensions;
	sf::Text text;
	sf::Color textColor, shadowColor;
};