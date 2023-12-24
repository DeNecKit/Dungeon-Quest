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
		const char *dataPath, PlayerDirection startDir,
		sf::String *savePath = nullptr, json *loadData = nullptr);
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
	static unsigned int GetNum();
	static Level *Level1(sf::String *savePath = nullptr, json *loadData = nullptr);
	static Level *Level2(sf::String *savePath = nullptr, json *loadData = nullptr);
	static Level *Level3(sf::String *savePath = nullptr, json *loadData = nullptr);
	static Level *Get();
	static bool IsAnyLevel();
	static void Change(Level*);
	static void Next();
	static void Save();
	static void Load(std::string path);
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
	sf::String *savePath;

	static inline Level *currentLevel = nullptr;
};