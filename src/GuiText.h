#pragma once

#include "Gui.h"

class GuiText : public Gui
{
public:
	GuiText(sf::Vector2f pos, GuiStyle style,
		const sf::String &str, sf::Font* font,
		unsigned int chSize, bool enabled = true);
	void ProcessEvent(const sf::Event&) override;
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow*) override;
private:
	sf::Text text;
};