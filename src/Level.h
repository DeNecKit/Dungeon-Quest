#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Level
{
public:
	Level(const sf::String &tilesetTexturePath,
		const char *dataPath, PlayerDirection startDir);
	~Level();
	void ProcessEvent(const sf::Event&);
	void Update(sf::Time deltaTime);
	void RenderGUI(sf::RenderWindow*);
	void RenderSFML(sf::RenderWindow*);

	static unsigned int TileSize();
	static Level Level1();

private:
	unsigned int width, height;
	unsigned int* tiles, * walls;
	sf::Texture tilesetTexture;
	Player *player;
};