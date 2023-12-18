#include "EnemyGoblinKing.h"
#include "../Gui/GuiProgressBar.h"

EnemyGoblinKing::EnemyGoblinKing(unsigned int pos)
	: Enemy(L"Король гоблинов",
		{ {Stat::HP, 75}, {Stat::ATK, 25}, {Stat::DEF, 10}, {Stat::AGI, 0} },
		"data/goblin-king.png", 64, sf::milliseconds(150),
		{ {BattleAnimationState::Idle, 4},
		  {BattleAnimationState::Attack, 8},
		  {BattleAnimationState::TakeHit, 5},
		  {BattleAnimationState::Death, 11} }, 4, 550.f)
{
	animationPassedTime = sf::milliseconds(std::rand() % 150);
	animationCurFrame = std::rand() % 4;
	if (pos != 1) throw new std::exception();
	position = sf::Vector2f(1920.f, 1080.f/2-size/2-100)
		* GameManager::ResCoefX();
}

sf::Vector2f EnemyGoblinKing::GetHealthBarPos()
{
	sf::Vector2f hbs = GuiProgressBar::GetHealthBarSize();
	float w = hbs.x, h = hbs.y;
	return sf::Vector2f(position.x-size+size/2-w/2, position.y+h*4);
}

sf::FloatRect EnemyGoblinKing::GetClickHitbox()
{
	sf::Vector2f pos = sf::Vector2f(position.x - size, position.y);
	const float coef = 0.75f;
	return sf::FloatRect(
		sf::Vector2f(pos.x+size/2*(1-coef), pos.y+size/2*(1-coef)),
		sf::Vector2f(size*coef, size*coef*1.25f));
}

bool EnemyGoblinKing::FinishedActionAnimation()
{
	return finishedAttack;
}

bool EnemyGoblinKing::FinishedHitAnimation()
{
	return finishedHit;
}

bool EnemyGoblinKing::FinishedDeathAnimation()
{
	return finishedDeath;
}

unsigned int EnemyGoblinKing::DropExp()
{
	return 100;
}

std::vector<Item*> EnemyGoblinKing::DropLoot()
{
	return {Item::Create(8, 1), Item::Create(7, 5)};
}