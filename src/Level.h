#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Tile/Tile.h"
#include "Item/ItemTemplate.h"
#include <vector>

class Level
{
public:
	Level(const sf::String &tilesetTexturePath,
		const char *dataPath, PlayerDirection startDir);
	~Level();
	void ProcessEvent(const sf::Event&);
	void Update(sf::Time deltaTime);
	void RenderSFML(sf::RenderWindow*);

	static unsigned int GetTileSize();
	static bool IsWall(unsigned int x, unsigned int y);
	static std::vector<Tile*> GetOtherTiles();
	static sf::Vector2f CalcTilePos(float x, float y, bool &isOnScreen);
	static void RenderTile(unsigned int id, float x, float y);
	static Level *Level1();
	static Level *Get();
	static void Change(Level*);
	static void Reset();

private:
	unsigned int width, height;
	std::vector<unsigned int> tiles, walls;
	std::vector<Tile*> otherTiles;
	sf::Texture tilesetTexture;
	Player *player;

	static inline Level *currentLevel = nullptr;
};