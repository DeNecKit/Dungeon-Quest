#pragma once

#include "Tile.h"
#include "../Item/Item.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class TileChest final : public Tile
{
public:
	TileChest(sf::Vector2u pos, json &content);
	bool IsWall() override;
	void ProcessEvent(const sf::Event&) override;
	Item* GetItem(unsigned int pos);
	void SetItem(unsigned int pos, Item* item);

private:
	Item *inventory[15] = {};
};