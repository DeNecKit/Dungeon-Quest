#include "Enemy.h"
#include "../GameManager.h"
#include "../Battle.h"
#include "../Scene/SceneBattle.h"

Enemy::Enemy(const sf::String &name, std::map<Stat, unsigned int> stats,
	const char *tilesetPath, unsigned int texSize, sf::Time animDeltaTime,
	std::map<BattleAnimationState, unsigned int> numOfFrames,
	unsigned int hitFrameNum, float size)
	: Entity(hitFrameNum), name(name), stats(stats), textureSize(texSize),
	numOfFrames(numOfFrames), size(size*GameManager::ResCoefX()), targetHover(nullptr),
	finishedAttack(false), finishedHit(false), finishedDeath(false)
{
	animationDeltaTime = animDeltaTime;
	animationTileset = new sf::Texture();
	if (!animationTileset->loadFromFile(tilesetPath))
		throw new std::exception();
	maxHP = stats[Stat::HP];
	hp = maxHP;
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
	if (!Battle::IsPlayerTurn() &&
		Battle::GetStage() == TurnStage::Waiting)
	{
		finishedAttack = false;
		finishedHit = false;
	}
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
		animationCurFrame++;
		bool animLastFrame = animationCurFrame == numOfFrames[battleAnimationState];
		if (battleAnimationState == BattleAnimationState::TakeHit && animLastFrame)
		{
			battleAnimationState = IsAlive()
				? BattleAnimationState::Idle : BattleAnimationState::Death;
			animationCurFrame = 0;
			animLastFrame = false;
			finishedHit = true;
		}
		if (battleAnimationState == BattleAnimationState::Death && animLastFrame)
		{
			finishedDeath = true;
			animationCurFrame--;
		}
		if (attack && animLastFrame)
		{
			finishedAttack = true;
			battleAnimationState = BattleAnimationState::Idle;
			animationCurFrame = 0;
		}
		else if (battleAnimationState == BattleAnimationState::Idle)
			animationCurFrame %= numOfFrames[battleAnimationState];
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
		if (!IsOut() && !Battle::IsEnd() && !SceneBattle::IsInventoryOpen())
			window->draw(*targetHover);
}

unsigned int Enemy::Attack()
{
	return stats[Stat::ATK];
}

void Enemy::TakeHit(unsigned int damage)
{
	int dmg = std::max((int)damage - (int)stats[Stat::DEF], 0);
	hp = std::max(hp - dmg, 0);
	battleAnimationState = BattleAnimationState::TakeHit;
	animationCurFrame = 0;
}

std::map<Stat, unsigned int> Enemy::GetStats()
{
	return stats;
}

unsigned int &Enemy::GetMaxHP()
{
	return maxHP;
}