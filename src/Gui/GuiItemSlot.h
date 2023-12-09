#pragma once

#include "Gui.h"
#include "GuiRect.h"
#include "GuiClickable.h"
#include "../Item/Item.h"

enum class SlotType
	{ Any, Sword, Helmet, Chestplate, Leggings, Boots };

class GuiItemSlot : public Gui
{
public:
	GuiItemSlot(sf::FloatRect dims,
		sf::Color fillColor, sf::Color textColor,
		SlotType type = SlotType::Any, Item *item = nullptr,
		sf::Color outlineColor = sf::Color::Transparent,
		sf::Color shadowColor = sf::Color::Transparent);
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;
	SlotType GetType();

	Item *item;

private:
	SlotType type;
	GuiRect rect;
	GuiClickable click;
	sf::Sprite sprite;
	sf::Vector2i lastMousePos;
	sf::Vector2f origPos;
};