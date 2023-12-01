#include "Level.h"
#include "GameManager.h"
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
	tiles = new unsigned int[width * height];
	walls = new unsigned int[width * height];
	for (int i = 0; i < (int)(width * height); i++)
	{
		tiles[i] = data["tiles"][i];
		walls[i] = data["walls"][i];
	}

	dataFile.close();
}

Level::~Level()
{
	delete tiles;
	delete player;
}

void Level::ProcessEvent(const sf::Event &event) {}

void Level::Update(sf::Time deltaTime)
{
	player->Update(deltaTime);
}

void Level::RenderGUI(sf::RenderWindow *window) {}

void Level::RenderSFML(sf::RenderWindow *window)
{
	window->clear(sf::Color(37, 19, 26));
	int ww = (int)window->getSize().x, wh = (int)window->getSize().y,
		px = (int)player->GetPos().x, py = (int)player->GetPos().y,
		ts = (int)TileSize();
	float left = px + ts / 2.f - ww / 2.f,
		right = px + ts / 2.f + ww / 2.f,
		top = py + ts / 2.f - wh / 2.f,
		bottom = py + ts / 2.f + wh / 2.f;
	for (int iy = 0; iy < (int)height; iy++)
		for (int ix = 0; ix < (int)width; ix++)
		{
			int tile = tiles[iy * width + ix];
			if (tile != 0)
			{
				float x = ix * ts - left;
				if (x + ts < 0 || x > right - left) continue;
				float y = iy * ts - top;
				if (y + ts < 0 || y > bottom - top) continue;
				int texSize = 16,
					texX = (tile - 1) % 10 * texSize,
					texY = (tile - 1) / 10 * texSize;
				sf::Sprite s(tilesetTexture, sf::IntRect(texX, texY, texSize, texSize));
				float factor = (float)ts / texSize;
				s.setScale(sf::Vector2f(factor, factor));
				s.setPosition(sf::Vector2f(x, y));
				window->draw(s);
			}
		}
	player->Render(window);
}

bool Level::IsWall(unsigned int x, unsigned int y)
{
	return currentLevel->walls[y * currentLevel->width + x];
}

unsigned int Level::TileSize()
{
	const unsigned int tileSize = 128;
	return tileSize * GameManager::WindowWidth() / 1920;
}

Level *Level::Level1()
{
	currentLevel = new Level(
		"data/tileset.png", "data/lvl-01.json", PlayerDirection::Right);
	return currentLevel;
}