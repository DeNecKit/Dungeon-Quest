#include "Level.h"
#include "GameManager.h"
#include "Tile/TileDoor.h"
#include "Tile/TileTorch.h"
#include "Tile/TileChest.h"
#include "SceneManager.h"
#include "Scene/SceneBattle.h"
#include "Scene/SceneGame.h"
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

auto *levels = new std::vector<Level*>();

Level::Level(unsigned int num, const sf::String &tilesetTexturePath,
	const char *dataPath, PlayerDirection startDir) : num(num), isBossDefeated(false)
{
	levels->push_back(this);

	if (!tilesetTexture.loadFromFile(tilesetTexturePath))
		throw std::exception();

	std::ifstream dataFile(dataPath);
	if (!dataFile.is_open())
		throw std::exception();
	json data = json::parse(dataFile);
	dataFile.close();

	unsigned int startPosX = data["start-pos"]["x"],
		startPosY = data["start-pos"]["y"];
	sf::Vector2u startPos(startPosX, startPosY);
	player = Player::Get() == nullptr
		? new Player(startPos, startDir) : Player::Get();
	Player::ResetBattleDist();
	if (Player::Get() == nullptr)
		player = new Player(startPos, startDir);
	else
	{
		player = Player::Get();
		player->SetStartPos(startPos);
	}

	width = data["width"];
	height = data["height"];
	for (int i = 0; i < (int)(width * height); i++)
	{
		tiles.push_back(data["tiles"][i]);
		walls.push_back(data["walls"][i]);
	}

	for (json &tilesData : data["other-tiles"])
	{
		int id = tilesData["id"];
		for (json &tileData : tilesData["tiles"])
		{
			unsigned int x = tileData["x"], y = tileData["y"];
			Tile *tile;
			switch (id)
			{
			case 36: case 37:
				tile = new TileDoor(id, sf::Vector2u(x, y));
				break;
			case 91:
				tile = new TileTorch(sf::Vector2u(x, y),
					tileData["type"] == "left");
				break;
			case 84:
				tile = new TileChest(sf::Vector2u(x, y), tileData["content"]);
				break;
			default:
				tile = new Tile(id, sf::Vector2u(x, y));
			}
			otherTiles.push_back(tile);
		}
	}

	bossTile = { (float)data["boss-tile"]["x"] * GetTileSize(),
				 (float)data["boss-tile"]["y"] * GetTileSize() };
	endTile = { (float)data["end-tile"]["x"] * GetTileSize(),
				(float)data["end-tile"]["y"] * GetTileSize() };
}

Level::~Level()
{
	for (int i = 0; i < levels->size(); i++)
		if (levels->at(i) == this) levels->at(i) = nullptr;
	auto levelsCopy = *levels;
	levels->clear();
	for (auto lvl : levelsCopy)
		if (lvl != nullptr) levels->push_back(lvl);
	if (!IsAnyLevel()) delete player;
	for (Tile *tile : otherTiles)
		delete tile;
}

void Level::ProcessEvent(const sf::Event &event)
{
	for (Tile *tile : otherTiles)
		tile->ProcessEvent(event);
}

void Level::Update(sf::Time deltaTime)
{
	for (Tile* tile : otherTiles)
		tile->Update(deltaTime);
	player->Update(deltaTime);
}

void Level::RenderSFML(sf::RenderWindow *window)
{
	window->clear(sf::Color(37, 19, 26));
	for (int iy = 0; iy < (int)height; iy++)
		for (int ix = 0; ix < (int)width; ix++)
		{
			int tile = tiles[iy * width + ix];
			if (tile != 0)
				RenderTile(tile - 1, ix * (float)GetTileSize(), iy * (float)GetTileSize());
		}
	for (Tile *tile : otherTiles) tile->Render(window);
	player->Render(window);
}

unsigned int Level::GetTileSize()
{
	const unsigned int tileSize = 128;
	return (int)(tileSize * GameManager::ResCoefX());
}

bool Level::IsWall(unsigned int x, unsigned int y)
{
	return currentLevel->walls[y * currentLevel->width + x];
}

std::vector<Tile*> Level::GetOtherTiles()
{
	return currentLevel->otherTiles;
}

sf::Vector2f Level::CalcTilePos(float x, float y, bool &isOnScreen)
{
	int ww = (int)GameManager::WindowWidth(),
		wh = (int)GameManager::WindowHeight(),
		px = (int)currentLevel->player->GetPos().x,
		py = (int)currentLevel->player->GetPos().y,
		ts = (int)GetTileSize();
	float left = px + ts / 2.f - ww / 2.f,
		right = px + ts / 2.f + ww / 2.f,
		top = py + ts / 2.f - wh / 2.f,
		bottom = py + ts / 2.f + wh / 2.f;
	x -= left; y -= top;
	isOnScreen = x + ts > 0 && x < ww && y + ts > 0 && y < wh;
	return sf::Vector2f(x, y);
}

void Level::RenderTile(unsigned int id, float x, float y)
{
	bool isOnScreen;
	sf::Vector2f tilePos = CalcTilePos(x, y, isOnScreen);
	if (!isOnScreen) return;
	
	int texSize = 16,
		texX = id % 10 * texSize,
		texY = id / 10 * texSize;
	sf::Sprite s(currentLevel->tilesetTexture,
		sf::IntRect(texX, texY, texSize, texSize));
	float factor = (float)GetTileSize() / texSize;
	s.setScale(sf::Vector2f(factor, factor));
	s.setPosition(sf::Vector2f(tilePos.x, tilePos.y));
	GameManager::GetWindow()->draw(s);
}

sf::Vector2f Level::GetBossTile()
{
	return currentLevel->bossTile;
}

sf::Vector2f Level::GetEndTile()
{
	return currentLevel->endTile;
}

bool Level::IsBossDefeated()
{
	return currentLevel->isBossDefeated;
}

bool Level::SetBossDefeated()
{
	return currentLevel->isBossDefeated = true;
}

unsigned int Level::GetNum()
{
	return currentLevel->num;
}

Level *Level::Level1()
{
	return new Level(1, "data/tileset.png", "data/lvl-01.json", PlayerDirection::Right);
}

Level *Level::Level2()
{
	return new Level(2, "data/tileset.png", "data/lvl-02.json", PlayerDirection::Right);
}

Level *Level::Level3()
{
	return new Level(3, "data/tileset.png", "data/lvl-03.json", PlayerDirection::Left);
}

Level *Level::Get()
{
	return currentLevel;
}

bool Level::IsAnyLevel()
{
	return levels->size() > 0;
}

void Level::Change(Level *level)
{
	delete currentLevel;
	currentLevel = level;
}

void Level::Next()
{
	Level *nextLevel;
	switch (currentLevel->num)
	{
	case 1: nextLevel = Level2(); break;
	case 2: nextLevel = Level3(); break;
	default: throw new std::exception();
	}
	Change(nextLevel);
}

void Level::Reset()
{
	if (currentLevel != nullptr)
		delete currentLevel;
	currentLevel = nullptr;
}

void Level::Shutdown()
{
	delete levels;
}