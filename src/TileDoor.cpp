#include "TileDoor.h"
#include "Player.h"
#include "Level.h"
#include "SceneGame.h"
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
		isOpen = event.type == sf::Event::KeyPressed
			&& event.key.code == sf::Keyboard::E;
	}
}

void TileDoor::Render(sf::RenderWindow *window)
{
	unsigned int tile = isOpen ? (id == 36 ? 48 : 47) : id;
	Level::RenderTile(tile, position.x, position.y);
}