#include "Enemy.h"
#include "../GameManager.h"

Enemy::Enemy(const sf::String& name, std::map<Stat, unsigned int> stats,
	const char* tilesetPath, unsigned int texSize, sf::Time animDeltaTime,
	std::map<BattleAnimationState, unsigned int> numOfFrames)
	: name(name), stats(stats), textureSize(texSize), numOfFrames(numOfFrames)
{
	animationDeltaTime = animDeltaTime;
	animationTileset = new sf::Texture();
	if (!animationTileset->loadFromFile(tilesetPath))
		throw new std::exception();
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
	float size = GameManager::WindowHeight() / 1.5f;
	s.setPosition((float)GameManager::WindowWidth(),
		GameManager::WindowHeight() / 2.f - size / 2.f);
	float factor = size / textureSize;
	s.setScale(factor * -1, factor);
	window->draw(s);
}

unsigned int Enemy::Attack()
{
	return stats[Stat::ATK];
}