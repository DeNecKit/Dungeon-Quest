#pragma once

#include <SFML/Graphics.hpp>
#include "Gui.h"

class GuiClickable final : public Gui
{
public:
	GuiClickable(sf::FloatRect dims,
		void (*onClick)(const sf::Event&), bool doHover = true);
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;
	bool IsPressed();
	bool IsHovered();

private:
	void (*OnClick)(const sf::Event&);
	bool isPressed, doHover, isHovered;
	sf::RectangleShape hoverRect;
};