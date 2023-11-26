#include "Level.h"

Level::Level(const sf::String &backLayerTexturePath)
	: player(Player(sf::Vector2f(50.f, 50.f),
		PlayerDirection::Up, sf::milliseconds(128)))
{
	if (!backLayerTexture.loadFromFile(backLayerTexturePath))
		throw std::exception();
	backLayerSprite = sf::Sprite(backLayerTexture);
}

void Level::ProcessEvent(const sf::Event &event) {}

void Level::Update(sf::Time deltaTime)
{
	player.Update(deltaTime);
}

void Level::RenderGUI(sf::RenderWindow *window) {}

void Level::RenderSFML(sf::RenderWindow *window)
{
	backLayerSprite.setTextureRect(sf::IntRect(0, 0, window->getSize().x, window->getSize().y));
	window->draw(backLayerSprite);
	player.Render(window);
}

Level Level::Level1()
{
	return Level("data/lvl-01.png");
}