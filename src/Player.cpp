#include "Player.h"
#include "Level.h"
#include "GameManager.h"
#include <cmath>

Player::Player(sf::Vector2u startPos, PlayerDirection startDir)
	: Entity(sf::milliseconds(128)), isInBattle(false),
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

void Player::Update(sf::Time deltaTime)
{
	float sprint = sf::Keyboard::isKeyPressed(
		sf::Keyboard::LControl) ? sprintCoef : 1.f;

	animationPassedTime += deltaTime;
	sf::Time animDT = animationDeltaTime / sprint;
	if (animationPassedTime >= animDT)
	{
		animationPassedTime -= animDT;
		unsigned int maxNum = isInBattle
			? numOfBattleFrames[battleAnimationState]
			: numOfFrames[animationState];
		animationCurFrame = (animationCurFrame + 1) % maxNum;
	}

	bool walking = false;
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
	sf::Sprite s(animationTileset,
		sf::IntRect(animationCurFrame * 16, 0, 16, 16));
	int right = direction == PlayerDirection::Right ? 1 : -1;
	s.setPosition(sf::Vector2f(
		GameManager::WindowWidth() / 2 - Level::TileSize() / 2.f * right,
		GameManager::WindowHeight() / 2 - Level::TileSize() / 2.f));
	float factor = Level::TileSize() / 16.f * sizeCoef;
	s.setScale(sf::Vector2f(factor * right, factor));
	window->draw(s);
}

void Player::TryMove(float deltaX, float deltaY)
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
			if (Level::IsWall(ix, iy)
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