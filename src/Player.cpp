#include "Player.h"
#include "Level.h"
#include "GameManager.h"
#include <cmath>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

Player::Player(sf::Vector2u startPos, PlayerDirection startDir)
	: isInBattle(false), direction(startDir),
	animationState(PlayerAnimationState::Idle)
{
	currentPlayer = this;
	animationDeltaTime = sf::milliseconds(128);
	position = sf::Vector2f(
		(float)(startPos.x * Level::GetTileSize()),
		(float)(startPos.y * Level::GetTileSize()));
	animationTileset = new sf::Texture();
	if (!animationTileset->loadFromFile("data/player.png"))
		throw std::exception();
	numOfFrames = {
		{ PlayerAnimationState::Idle, 1 },
		{ PlayerAnimationState::Walking, 4 }
	};
	stats = {{Stat::HP, 40}, {Stat::ATK, 5}, {Stat::DEF, 5}, {Stat::AGI, 5}};
	std::ifstream dataFile("data/player.json");
	if (!dataFile.is_open())
		throw std::exception();
	json data = json::parse(dataFile);
	dataFile.close();
	for (int i = 0; i < 20; i++)
		inventory[i] = nullptr;
	for (json &item : data["start-inventory"])
		inventory[item["pos"]] = Item::Create(item["id"], item["count"]);
}

void Player::Update(sf::Time deltaTime)
{
	float sprint = sf::Keyboard::isKeyPressed(
		sf::Keyboard::LControl) ? sprintCoef : 1.f;

	animationPassedTime += deltaTime;
	if (animationPassedTime >= animationDeltaTime / sprint)
	{
		animationPassedTime = sf::Time::Zero;
		unsigned int maxNum = isInBattle
			? numOfBattleFrames[battleAnimationState]
			: numOfFrames[animationState];
		animationCurFrame = (animationCurFrame + 1) % maxNum;
	}

	bool walking = false;
	float speed = this->speed * GameManager::ResCoefX();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		walking = true;
		direction = PlayerDirection::Right;
		TryMove(speed * sprint * deltaTime.asSeconds(), 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		walking = true;
		direction = PlayerDirection::Left;
		TryMove(-speed * sprint * deltaTime.asSeconds(), 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		walking = true;
		TryMove(0.f, speed * sprint * deltaTime.asSeconds());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		walking = true;
		TryMove(0.f, -speed * sprint * deltaTime.asSeconds());
	}
	if (walking) animationState = PlayerAnimationState::Walking;
	else animationState = PlayerAnimationState::Idle;
}

void Player::Render(sf::RenderWindow *window)
{
	sf::Sprite s(*animationTileset,
		sf::IntRect(animationCurFrame * 16, 0, 16, 16));
	int right = direction == PlayerDirection::Right ? 1 : -1;
	s.setPosition(sf::Vector2f(
		GameManager::WindowWidth() / 2 - Level::GetTileSize() * sizeCoef / 2.f * right,
		GameManager::WindowHeight() / 2 - Level::GetTileSize() * sizeCoef / 2.f));
	float factor = Level::GetTileSize() / 16.f * sizeCoef;
	s.setScale(sf::Vector2f(factor * right, factor));
	window->draw(s);
}

void Player::TryMove(float deltaX, float deltaY)
{
	sf::Vector2f newPos = sf::Vector2f(
		position.x + deltaX,
		position.y + deltaY);
	float tileSize = (float)Level::GetTileSize(),
		playerSize = tileSize * sizeCoef,
		px = newPos.x, py = newPos.y;
	for (Tile *tile : Level::GetOtherTiles())
	{
		float x = tile->GetPos().x, y = tile->GetPos().y;
		if (tile->IsWall()
			&& px + playerSize > x && px < x + playerSize
			&& py + playerSize > y && py < y + playerSize)
			newPos = GetFixedPos(deltaX, deltaY, newPos, playerSize, x, y);
	}
	for (int dx = -1; dx <= 1; dx++)
		for (int dy = -1; dy <= 1; dy++)
		{
			if (dx == 0 && dy == 0) continue;
			float x = newPos.x + tileSize * dx,
				y = newPos.y + tileSize * dy;
			int ix = (int)std::roundf(x / tileSize),
				iy = (int)std::roundf(y / tileSize);
			x = ix * tileSize, y = iy * tileSize;
			if (Level::IsWall(ix, iy)
				&& px + playerSize > x && px < x + playerSize
				&& py + playerSize > y && py < y + playerSize)
				newPos = GetFixedPos(deltaX, deltaY, newPos, playerSize, x, y);
		}
	position = newPos;
}

sf::Vector2f Player::GetFixedPos(float deltaX, float deltaY,
	sf::Vector2f playerPos, float playerSize,
	float otherX, float otherY)
{
	if (deltaX > 0)
		playerPos = sf::Vector2f(otherX - playerSize, playerPos.y);
	else if (deltaX < 0)
		playerPos = sf::Vector2f(otherX + playerSize, playerPos.y);
	else if (deltaY > 0)
		playerPos = sf::Vector2f(playerPos.x, otherY - playerSize);
	else if (deltaY < 0)
		playerPos = sf::Vector2f(playerPos.x, otherY + playerSize);
	return playerPos;
}

sf::Vector2f Player::GetPos()
{
	return currentPlayer->position;
}

float Player::GetSize()
{
	return Level::GetTileSize() * sizeCoef;
}

Item * Player::GetItemAt(unsigned int pos)
{
	return currentPlayer->inventory[pos];
}