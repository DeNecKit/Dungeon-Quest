#include "Level.h"

Level::Level(const sf::String &backLayerTexturePath)
	: player(Player(sf::Vector2f(1472.f, 1280.f),
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
	int ww = window->getSize().x, wh = window->getSize().y,
		px = (int)player.GetPos().x, py = (int)player.GetPos().y;
	backLayerSprite.setTextureRect(sf::IntRect(
		px + CELL_SIZE / 2 - ww / 2, py + CELL_SIZE / 2 - wh / 2, ww, wh));
	window->draw(backLayerSprite);
	player.Render(window);
}

Level Level::Level1()
{
	return Level("data/lvl-01.png");
}