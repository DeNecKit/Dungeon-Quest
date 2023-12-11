#pragma once

#include "Gui.h"
#include "GuiRect.h"
#include "GuiClickable.h"
#include "../Item/Item.h"
#include "../Entity/Player.h"
#include "../Tile/TileChest.h"

enum class SlotType
	{ Any, Sword, Helmet, Chestplate, Leggings, Boots };

class GuiItemSlot : public Gui
{
public:
	GuiItemSlot(sf::FloatRect dims, TileChest *parentChest,
		unsigned int pos, SlotType type = SlotType::Any,
		Item *item = nullptr);
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;
	unsigned int GetPos();

	Item *item;
	SlotType type;
	TileChest *parentChest;

private:
	GuiRect rect;
	GuiClickable click;
	sf::Sprite sprite;
	sf::Vector2i lastMousePos;
	sf::Vector2f origPos;
	unsigned int pos;
};