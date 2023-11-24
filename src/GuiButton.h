#pragma once

#include "Gui.h"

class GuiButton : public Gui
{
public:
	GuiButton(sf::Vector2f pos, sf::Vector2f size,
		GuiStyle style, const sf::String &str,
		sf::Font* font, unsigned int chSize,
		void (*onClick)(const sf::Event&),
		void (*onHover)(const sf::Event&) = nullptr,
		bool enabled = true);
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;
private:
	sf::RectangleShape rect;
	sf::Text text;
	void (*OnClick)(const sf::Event&);
	void (*OnHover)(const sf::Event&);
	bool isHovered;
};