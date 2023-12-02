#include "TileTorch.h"
#include "../Level.h"

TileTorch::TileTorch(sf::Vector2u pos, bool left)
	: Tile(0, pos), left(left)
{
	animationDeltaTime = sf::milliseconds(128);
	if (tileset == nullptr)
	{
		tileset = new sf::Texture();
		if (!tileset->loadFromFile("data/torch.png"))
			throw std::exception();
	}
	animationTileset = tileset;
}

TileTorch::~TileTorch()
{
	animationTileset = nullptr;
	if (tileset == nullptr) return;
	delete tileset;
	tileset = nullptr;
}

void TileTorch::Update(sf::Time deltaTime)
{
	animationPassedTime += deltaTime;
	if (animationPassedTime >= animationDeltaTime)
	{
		animationPassedTime = sf::Time::Zero;
		animationCurFrame = (animationCurFrame + 1) % 4;
	}
}

void TileTorch::Render(sf::RenderWindow *window)
{
	sf::Sprite s(*animationTileset,
		sf::IntRect(animationCurFrame * 16, 0, 16, 16));
	bool isOnScreen;
	sf::Vector2f pos = Level::CalcTilePos(position.x, position.y, isOnScreen);
	if (!isOnScreen) return;
	float tileSize = (float)Level::GetTileSize();
	s.setPosition(pos.x + (left ? 0 : tileSize), pos.y);
	float factor = Level::GetTileSize() / 16.f;
	s.setScale(sf::Vector2f(factor * (left ? 1.f : -1.f), factor));
	window->draw(s);
}