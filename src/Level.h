#pragma once

#include <SFML/Graphics.hpp>
#include "Entity/Player.h"
#include "Tile/Tile.h"
#include "Item/ItemTemplate.h"
#include <vector>

class Level
{
public:
	Level(unsigned int num, const sf::String &tilesetTexturePath,
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
	static sf::Vector2f GetBossTile();
	static sf::Vector2f GetEndTile();
	static bool IsBossDefeated();
	static bool SetBossDefeated();
	static Level *Level1();
	static Level *Level2();
	static Level *Get();
	static bool IsAnyLevel();
	static void Change(Level*);
	static void Next();
	static void Reset();
	static void Shutdown();

private:
	unsigned int num, width, height;
	std::vector<unsigned int> tiles, walls;
	std::vector<Tile*> otherTiles;
	sf::Texture tilesetTexture;
	Player *player;
	sf::Vector2f bossTile, endTile;
	bool isBossDefeated;

	static inline Level *currentLevel = nullptr;
};