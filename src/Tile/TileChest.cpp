#include "TileChest.h"
#include "../Level.h"
#include "../Scene/SceneGame.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

TileChest::TileChest(sf::Vector2u pos, json &content)
	: Tile(84, pos)
{
	for (int i = 0; i < 15; i++) inventory[i] = nullptr;
	for (json &itemData : content)
		inventory[itemData["pos"]] = Item::Create(
			itemData["id"], itemData["count"]);
}

bool TileChest::IsWall()
{
	return true;
}

void TileChest::ProcessEvent(const sf::Event &event)
{
	float px = Player::GetPos().x, py = Player::GetPos().y,
		x = position.x, y = position.y,
		tileSize = (float)Level::GetTileSize();
	if (std::abs(px - x) < tileSize * 1.2f &&
		std::abs(py - y) < tileSize * 1.2f)
	{
		SceneGame::InteractionNotify();
		if (event.type == sf::Event::KeyPressed
			&& event.key.code == sf::Keyboard::F)
			SceneGame::OpenChest(this);
	}
}

Item* TileChest::GetItem(unsigned int pos)
{
	return inventory[pos];
}

void TileChest::SetItem(unsigned int pos, Item *item)
{
	inventory[pos] = item;
}