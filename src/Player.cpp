#include "Player.h"
#include "Level.h"
#include "GameManager.h"

Player::Player(sf::Vector2f startPos,
	PlayerDirection startDir, sf::Time animDeltaTime)
	: Entity(animDeltaTime), isInBattle(false),
	position(startPos), direction(startDir),
	animationState(PlayerAnimationState::Idle)
{
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
}

void Player::Render(sf::RenderWindow *window)
{
	sf::Sprite s(animationTileset,
		sf::IntRect(animationCurFrame * 16, 0, 16, 16));
	s.setPosition(sf::Vector2f(
		GameManager::WindowWidth() / 2 - Level::CELL_SIZE / 2.f,
		GameManager::WindowHeight() / 2 - Level::CELL_SIZE / 2.f));
	float factor = Level::CELL_SIZE / 16.f;
	s.setScale(sf::Vector2f(factor, factor));
	window->draw(s);
}