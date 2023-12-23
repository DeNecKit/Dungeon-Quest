#include "EnemyReaper.h"
#include "../Gui/GuiProgressBar.h"
#include <cstdlib>

EnemyReaper::EnemyReaper(unsigned int pos)
	: Enemy("∆нец",
		{ {Stat::HP, 100}, {Stat::ATK, 65}, {Stat::DEF, 30}, {Stat::AGI, 5} },
		"data/reaper.png", 140, sf::milliseconds(100),
		{ {BattleAnimationState::Idle, 8},
		  {BattleAnimationState::Attack, 10},
		  {BattleAnimationState::TakeHit, 3},
		  {BattleAnimationState::Death, 11} }, 4, 750.f, false)
{
	animationPassedTime = sf::milliseconds(std::rand() % 150);
	animationCurFrame = std::rand() % 8;
	float ww = 1920.f, wh = 1080.f;
	if (pos != 1) throw new std::exception();
	position = sf::Vector2f(ww-size-100, wh/2-size/2+50);
	position *= GameManager::ResCoefX();
}

sf::Vector2f EnemyReaper::GetHealthBarPos()
{
	sf::Vector2f hbs = GuiProgressBar::GetHealthBarSize();
	float w = hbs.x, h = hbs.y;
	return sf::Vector2f(position.x+size/2-w/2+200.f, position.y+h*4);
}

sf::FloatRect EnemyReaper::GetClickHitbox()
{
	sf::Vector2f pos = sf::Vector2f(position.x, position.y);
	const float coef = 0.6f;
	return sf::FloatRect(
		pos.x+size/2*(1-coef)+200, pos.y+size/2*(1-coef)-60,
		size*coef, size*coef);
}

unsigned int EnemyReaper::DropExp()
{
	return 200;
}

std::vector<Item*> EnemyReaper::DropLoot()
{
	return {Item::Create(16, 1), Item::Create(24, 5), Item::Create(25, 1)};
}
