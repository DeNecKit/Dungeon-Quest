#include "Player.h"
#include "../Level.h"
#include "../GameManager.h"
#include <cmath>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <cstdlib>
#include "../Scene/SceneBattle.h"
#include "../Battle.h"
#include "EnemyGoblin.h"

Player::Player(sf::Vector2u startPos, PlayerDirection startDir)
	: isInBattle(false), direction(startDir),
	animationState(PlayerAnimationState::Idle), walkedDistance(0.f),
	requiredDistance(GenerateRequiredDistance())
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
	numOfBattleFrames = {
		{ BattleAnimationState::Idle, 6 },
		{ BattleAnimationState::Attack,	6 },
		{ BattleAnimationState::TakeHit, 3 },
		{ BattleAnimationState::Death, 6 }
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
	if (isInBattle) UpdateInBattle(deltaTime);
	else UpdateInGame(deltaTime);
}

void Player::Render(sf::RenderWindow *window)
{
	if (isInBattle) RenderInBattle(window);
	else RenderInGame(window);
}

unsigned int Player::Attack()
{
	unsigned int res = stats[Stat::ATK];
	for (int i = 14; i < 20; i++)
		res += inventory[i]->GetTemplate()->GetStats()[Stat::ATK];
	return res;
}

void Player::UpdateInGame(sf::Time deltaTime)
{
	float sprint = sf::Keyboard::isKeyPressed(
		sf::Keyboard::LShift) ? sprintCoef : 1.f;

	animationPassedTime += deltaTime;
	if (animationPassedTime >= animationDeltaTime / sprint)
	{
		animationPassedTime = sf::Time::Zero;
		animationCurFrame = (animationCurFrame + 1)
			% numOfFrames[animationState];
	}

	bool walking = false;
	float speed = this->speed * GameManager::ResCoefX(),
		deltaDist = speed * sprint * deltaTime.asSeconds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		walking = true;
		direction = PlayerDirection::Right;
		TryMove(deltaDist, 0.f);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		walking = true;
		direction = PlayerDirection::Left;
		TryMove(-deltaDist, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		walking = true;
		TryMove(0.f, deltaDist);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		walking = true;
		TryMove(0.f, -deltaDist);
	}
	if (walking)
	{
		animationState = PlayerAnimationState::Walking;
		walkedDistance += deltaDist;
		if (walkedDistance > requiredDistance)
		{
			walkedDistance = 0.f;
			requiredDistance = GenerateRequiredDistance();
			Battle::Start(this, {new EnemyGoblin()});
		}
	} else animationState = PlayerAnimationState::Idle;
}

void Player::UpdateInBattle(sf::Time deltaTime)
{
	animationPassedTime += deltaTime;
	if (animationPassedTime >= animationDeltaTime)
	{
		animationPassedTime = sf::Time::Zero;
		animationCurFrame = (animationCurFrame + 1)
			% numOfBattleFrames[battleAnimationState];
	}
}

void Player::RenderInGame(sf::RenderWindow *window)
{
	unsigned int texSize = 16;
	sf::Sprite s(*animationTileset,
		sf::IntRect(animationCurFrame * texSize, 0, texSize, texSize));
	int right = direction == PlayerDirection::Right ? 1 : -1;
	s.setPosition(sf::Vector2f(
		GameManager::WindowWidth() / 2 - Level::GetTileSize() * sizeCoef / 2.f * right,
		GameManager::WindowHeight() / 2 - Level::GetTileSize() * sizeCoef / 2.f));
	float factor = Level::GetTileSize() / 16.f * sizeCoef;
	s.setScale(sf::Vector2f(factor * right, factor));
	window->draw(s);
}

void Player::RenderInBattle(sf::RenderWindow* window)
{
	unsigned int texSize = 64;
	sf::Sprite s(*animationTileset,
		sf::IntRect(animationCurFrame * texSize,
			16 + (int)battleAnimationState * texSize, texSize, texSize));
	float size = GameManager::WindowHeight() / 2.f;
	s.setPosition(0.f, GameManager::WindowHeight() / 2.f - size / 2.f);
	float factor = size / texSize;
	s.setScale(factor, factor);
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

float Player::GenerateRequiredDistance()
{
	//return std::rand() / (float)RAND_MAX * 8*speed + 7*speed;
	return 300.f;
}

sf::Vector2f Player::GetPos()
{
	return currentPlayer->position;
}

float Player::GetSize()
{
	return Level::GetTileSize() * sizeCoef;
}

Item* Player::GetItem(unsigned int pos)
{
	return currentPlayer->inventory[pos];
}

void Player::SetItem(unsigned int pos, Item *item)
{
	currentPlayer->inventory[pos] = item;
}

void Player::InBattle(bool set)
{
	currentPlayer->isInBattle = set;
	currentPlayer->animationCurFrame = 0;
}