#pragma once

#include "Gui.h"
#include "GuiRect.h"
#include "../Item/Item.h"
#include "../Entity/Player.h"
#include "../Tile/TileChest.h"
#include <vector>

class GuiList : public Gui
{
public:
	GuiList(sf::FloatRect dims, sf::Color fillColor = MenuFillColor,
		sf::Color outlineColor = MenuOutlineColor);
	~GuiList();
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;
	void Append(Gui *element);
	std::vector<Gui*> GetChildren();
	void SetItem(unsigned int pos, Item *item);
	void SetParent(unsigned int pos,  TileChest *parentChest);

private:
	GuiRect rect;
	std::vector<Gui*> children;
};