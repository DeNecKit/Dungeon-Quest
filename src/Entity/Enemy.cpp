#include "Enemy.h"
#include "../GameManager.h"
#include "../Battle.h"

Enemy::Enemy(const sf::String &name, std::map<Stat, unsigned int> stats,
	const char *tilesetPath, unsigned int texSize, sf::Time animDeltaTime,
	std::map<BattleAnimationState, unsigned int> numOfFrames,
	unsigned int hitFrameNum, float size)
	: Entity(hitFrameNum), name(name), stats(stats), textureSize(texSize),
	numOfFrames(numOfFrames), size(size*GameManager::ResCoefX()),
	targetHover(nullptr), finishedAttack(false)
{
	animationDeltaTime = animDeltaTime;
	animationTileset = new sf::Texture();
	if (!animationTileset->loadFromFile(tilesetPath))
		throw new std::exception();
	hp = stats[Stat::HP];
}

Enemy::~Enemy()
{
	delete targetHover;
}

void Enemy::ProcessEvent(const sf::Event &event)
{
	if (targetHover == nullptr)
	{
		targetHover = new sf::RectangleShape(GetClickHitbox().getSize());
		targetHover->setPosition(GetClickHitbox().getPosition());
		targetHover->setFillColor(sf::Color(255, 255, 255, 50));
		targetHover->setOutlineThickness(0.5f);
		targetHover->setOutlineColor(sf::Color(0, 0, 0, 50));
	}
	if (GameManager::IsMouseOver(GetClickHitbox()) &&
		Battle::IsPlayerTurn() && Battle::GetStage() == TurnStage::Waiting
		&& event.type == sf::Event::MouseButtonPressed)
		Battle::Get()->target = this;
}

void Enemy::Update(sf::Time deltaTime)
{
	if (Battle::GetStage() == TurnStage::Waiting) finishedAttack = false;
	bool attack = Battle::GetTurnMaker() == this && !finishedAttack
		&& Battle::GetStage() == TurnStage::Action
		&& Battle::GetChosenAction() == TurnAction::Attack;
	if (battleAnimationState != BattleAnimationState::Attack && attack)
	{
		battleAnimationState = BattleAnimationState::Attack;
		animationCurFrame = 0;
	}
	animationPassedTime += deltaTime;
	if (animationPassedTime >= animationDeltaTime)
	{
		animationPassedTime = sf::Time::Zero;
		if (attack)
		{
			if (++animationCurFrame == numOfFrames[battleAnimationState])
			{
				finishedAttack = true;
				battleAnimationState = BattleAnimationState::Idle;
				animationCurFrame = 0;
			}
		}
		else animationCurFrame = (animationCurFrame + 1)
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
	if (GameManager::IsMouseOver(GetClickHitbox()) &&
		Battle::IsPlayerTurn() && Battle::GetStage() == TurnStage::Waiting)
		window->draw(*targetHover);
}

unsigned int Enemy::Attack()
{
	return stats[Stat::ATK];
}

std::map<Stat, unsigned int> Enemy::GetStats()
{
	return stats;
}