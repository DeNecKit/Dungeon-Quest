#pragma once

#include "Gui.h"

class GuiText : public Gui
{
public:
	GuiText(sf::Vector2f pos, sf::Vector2f size,
		GuiStyle style, const sf::String &str,
		sf::Font* font, unsigned int chSize, bool enabled = true);
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;
private:
	sf::Text text;
};