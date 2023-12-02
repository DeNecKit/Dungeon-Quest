#pragma once

#include "Tile.h"
#include "../Animatable.h"

class TileTorch final : public Tile
{
public:
	TileTorch(sf::Vector2u pos, bool left);
	~TileTorch();
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;

private:
	bool left;

	static inline sf::Texture *tileset;
};