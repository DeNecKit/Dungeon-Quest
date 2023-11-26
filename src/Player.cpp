#include "Player.h"

Player::Player(sf::Vector2f startPos,
	PlayerDirection startDir, sf::Time animDeltaTime)
	: Entity(animDeltaTime), isInBattle(false),
	position(startPos), direction(startDir),
	animationState(PlayerAnimationState::Walking)
{
	if (!animationTileset.loadFromFile("data/player.png"))
		throw std::exception();
	numOfFrames = {
		{ PlayerAnimationState::Idle, 1 },
		{ PlayerAnimationState::Walking, 4 }
	};
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
	s.setPosition(position);
	s.setScale(sf::Vector2f(5.f, 5.f));
	window->draw(s);
}