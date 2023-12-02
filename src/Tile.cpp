#include "Tile.h"
#include "Level.h"

Tile::Tile(unsigned int id, sf::Vector2u pos)
	: id(id), position(sf::Vector2f(
		(float)pos.x * Level::GetTileSize(),
		(float)pos.y * Level::GetTileSize())) {}

bool Tile::IsWall()
{
	return false;
}

void Tile::Update(sf::Time deltaTime) {}

void Tile::ProcessEvent(const sf::Event &event) {}

void Tile::Render(sf::RenderWindow *window)
{
	Level::RenderTile(id, position.x, position.y);
}

unsigned int Tile::GetId()
{
	return id;
}

sf::Vector2f Tile::GetPos()
{
	return position;
}