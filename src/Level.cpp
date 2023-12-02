#include "Level.h"
#include "GameManager.h"
#include "TileDoor.h"
#include "TileTorch.h"
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

Level::Level(const sf::String &tilesetTexturePath,
	const char *dataPath, PlayerDirection startDir)
{
	if (!tilesetTexture.loadFromFile(tilesetTexturePath))
		throw std::exception();

	std::ifstream dataFile(dataPath);
	if (!dataFile.is_open())
		throw std::exception();
	json data = json::parse(dataFile);

	unsigned int startPosX = data["start-pos"]["x"],
		startPosY = data["start-pos"]["y"];
	sf::Vector2u startPos(startPosX, startPosY);
	player = new Player(startPos, startDir);

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
			default:
				tile = new Tile(id, sf::Vector2u(x, y));
			}
			otherTiles.push_back(tile);
		}
	}

	dataFile.close();
}

Level::~Level()
{
	delete player;
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

void Level::RenderGUI(sf::RenderWindow *window) {}

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
	// TODO: some tiles in front of character, some behind
	player->Render(window);
}

unsigned int Level::GetTileSize()
{
	const unsigned int tileSize = 128;
	return tileSize * (int)GameManager::ResCoefX();
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

Level *Level::Level1()
{
	currentLevel = new Level(
		"data/tileset.png", "data/lvl-01.json", PlayerDirection::Right);
	return currentLevel;
}