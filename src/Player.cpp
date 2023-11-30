#include "Player.h"
#include "Level.h"
#include "GameManager.h"
#include <cmath>

Player::Player(sf::Vector2u startPos,
	PlayerDirection startDir, sf::Time animDeltaTime)
	: Entity(animDeltaTime), isInBattle(false),
	direction(startDir), animationState(PlayerAnimationState::Idle)
{
	position = sf::Vector2f(
		(float)(startPos.x * Level::TileSize()),
		(float)(startPos.y * Level::TileSize()));
	if (!animationTileset.loadFromFile("data/player.png"))
		throw std::exception();
	numOfFrames = {
		{ PlayerAnimationState::Idle, 1 },
		{ PlayerAnimationState::Walking, 4 }
	};
}

sf::Vector2f Player::GetPos()
{
	return position;
}

void Player::Update(sf::Time deltaTime,
	unsigned int* walls, unsigned int width)
{
	animationPassedTime += deltaTime;
	if (animationPassedTime >= animationDeltaTime)
	{
		animationPassedTime -= animationDeltaTime;
		unsigned int maxNum = isInBattle
			? numOfBattleFrames[battleAnimationState]
			: numOfFrames[animationState];
		animationCurFrame = (animationCurFrame + 1) % maxNum;
	}

	float sprint = sf::Keyboard::isKeyPressed(
		sf::Keyboard::LControl) ? 1.5f : 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		TryMove(speed * sprint * deltaTime.asSeconds(), 0.f, walls, width);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		TryMove(-speed * sprint * deltaTime.asSeconds(), 0.f, walls, width);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		TryMove(0.f, speed * sprint * deltaTime.asSeconds(), walls, width);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		TryMove(0.f, -speed * sprint * deltaTime.asSeconds(), walls, width);
}

void Player::Render(sf::RenderWindow *window)
{
	sf::Sprite s(animationTileset,
		sf::IntRect(animationCurFrame * 16, 0, 16, 16));
	s.setPosition(sf::Vector2f(
		GameManager::WindowWidth() / 2 - Level::TileSize() / 2.f,
		GameManager::WindowHeight() / 2 - Level::TileSize() / 2.f));
	float factor = Level::TileSize() / 16.f * sizeCoef;
	s.setScale(sf::Vector2f(factor, factor));
	window->draw(s);
}

void Player::TryMove(float deltaX, float deltaY, unsigned int *walls, unsigned int width)
{
	sf::Vector2f newPos = sf::Vector2f(
		position.x + deltaX,
		position.y + deltaY);
	float tileSize = (float)Level::TileSize(),
		playerSize = tileSize * sizeCoef,
		px = newPos.x, py = newPos.y;
	for (int dx = -1; dx <= 1; dx++)
		for (int dy = -1; dy <= 1; dy++)
		{
			if (dx == 0 && dy == 0) continue;
			float x = newPos.x + tileSize * dx,
				y = newPos.y + tileSize * dy;
			int ix = (int)std::roundf(x / tileSize),
				iy = (int)std::roundf(y / tileSize);
			x = ix * tileSize, y = iy * tileSize;
			if (walls[iy * width + ix]
				&& px + playerSize > x && px < x + playerSize
				&& py + playerSize > y && py < y + playerSize)
			{
				if (deltaX > 0)
					newPos = sf::Vector2f(x - playerSize, newPos.y);
				else if (deltaX < 0)
					newPos = sf::Vector2f(x + playerSize, newPos.y);
				else if (deltaY > 0)
					newPos = sf::Vector2f(newPos.x, y - playerSize);
				else if (deltaY < 0)
					newPos = sf::Vector2f(newPos.x, y + playerSize);
			}
		}
	position = newPos;
}