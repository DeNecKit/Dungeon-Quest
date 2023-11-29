#include "Player.h"
#include "Level.h"
#include "GameManager.h"

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

void Player::Update(sf::Time deltaTime)
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
		TryMove(speed * sprint * deltaTime.asSeconds(), 0.f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		TryMove(-speed * sprint * deltaTime.asSeconds(), 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		TryMove(0.f, speed * sprint * deltaTime.asSeconds());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		TryMove(0.f, -speed * sprint * deltaTime.asSeconds());
}

void Player::Render(sf::RenderWindow *window)
{
	sf::Sprite s(animationTileset,
		sf::IntRect(animationCurFrame * 16, 0, 16, 16));
	s.setPosition(sf::Vector2f(
		GameManager::WindowWidth() / 2 - Level::TileSize() / 2.f,
		GameManager::WindowHeight() / 2 - Level::TileSize() / 2.f));
	float factor = Level::TileSize() / 16.f;
	s.setScale(sf::Vector2f(factor, factor));
	window->draw(s);
}

void Player::TryMove(float deltaX, float deltaY)
{
	// TODO: Collisions
	position = sf::Vector2f(
		position.x + deltaX,
		position.y + deltaY);
}