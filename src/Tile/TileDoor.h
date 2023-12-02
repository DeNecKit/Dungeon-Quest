#pragma once

#include "Tile.h"

class TileDoor final : public Tile
{
public:
	TileDoor(unsigned int id, sf::Vector2u pos);
	bool IsWall() override;
	void ProcessEvent(const sf::Event&) override;
	void Render(sf::RenderWindow*) override;

private:
	bool isOpen;
};