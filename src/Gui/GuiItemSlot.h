#pragma once

#include "Gui.h"
#include "GuiRect.h"
#include "GuiClickable.h"
#include "../Item/Item.h"

class GuiItemSlot : public Gui
{
public:
	GuiItemSlot(sf::FloatRect dims, Item*,
		sf::Color fillColor, sf::Color textColor,
		sf::Color outlineColor = sf::Color::Transparent,
		sf::Color shadowColor = sf::Color::Transparent);
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;

private:
	GuiRect rect;
	GuiClickable click;
	Item *item;
};