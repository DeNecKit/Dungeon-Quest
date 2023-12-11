#include "Enemy.h"
#include "../GameManager.h"

Enemy::Enemy(const sf::String& name, std::map<Stat, unsigned int> stats,
	const char* tilesetPath, unsigned int texSize, sf::Time animDeltaTime,
	std::map<BattleAnimationState, unsigned int> numOfFrames,
	unsigned int hitFrameNum, float size)
	: Entity(hitFrameNum), name(name), stats(stats), textureSize(texSize),
	numOfFrames(numOfFrames), size(size * GameManager::ResCoefX())
{
	animationDeltaTime = animDeltaTime;
	animationTileset = new sf::Texture();
	if (!animationTileset->loadFromFile(tilesetPath))
		throw new std::exception();
	hp = stats[Stat::HP];
}

void Enemy::Update(sf::Time deltaTime)
{
	animationPassedTime += deltaTime;
	if (animationPassedTime >= animationDeltaTime)
	{
		animationPassedTime = sf::Time::Zero;
		animationCurFrame = (animationCurFrame + 1)
			% numOfFrames[battleAnimationState];
	}
}

void Enemy::Render(sf::RenderWindow *window)
{
	sf::Sprite s(*animationTileset,
		sf::IntRect(animationCurFrame * textureSize,
			(int)battleAnimationState * textureSize,
			textureSize, textureSize));
	s.setPosition(position);
	float factor = size / textureSize;
	s.setScale(factor * -1, factor);
	window->draw(s);
}

unsigned int Enemy::Attack()
{
	return stats[Stat::ATK];
}

std::map<Stat, unsigned int> Enemy::GetStats()
{
	return stats;
}