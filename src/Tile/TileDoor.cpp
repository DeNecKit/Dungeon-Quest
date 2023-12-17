#include "TileDoor.h"
#include "../Entity/Player.h"
#include "../Level.h"
#include "../Scene/SceneGame.h"
#include <cmath>

TileDoor::TileDoor(unsigned int id, sf::Vector2u pos)
	: Tile(id, pos), isOpen(false) {}

bool TileDoor::IsWall()
{
	return !isOpen;
}

void TileDoor::ProcessEvent(const sf::Event &event)
{
	if (isOpen) return;
	float px = Player::GetPos().x, py = Player::GetPos().y,
		x = position.x, y = position.y,
		tileSize = (float)Level::GetTileSize();
	if (std::abs(px - x) < tileSize * 1.2f &&
		std::abs(py - y) < tileSize * 1.2f)
	{
		SceneGame::InteractionNotify();
		if (event.type == sf::Event::KeyPressed
			&& event.key.code == sf::Keyboard::F)
			if (id == 37 && Player::HasItem(ItemTemplate::Get(6)))
			{
				isOpen = true;
				Item *key = nullptr;
				for (int i = 0; i < 20; i++)
				{
					Item *item = Player::GetItem(i);
					if (item != nullptr && item->GetTemplate() == ItemTemplate::Get(6))
					{
						key = item;
						break;
					}
				}
				if (key == nullptr) throw new std::exception();
				key->Use();
				SceneGame::RefreshPlayerInventory();
			} else isOpen = id != 37;
	}
}

void TileDoor::Render(sf::RenderWindow *window)
{
	unsigned int tile = isOpen ? (id == 36 ? 48 : 47) : id;
	Level::RenderTile(tile, position.x, position.y);
}