#include "EnemyReaper.h"
#include "../Gui/GuiProgressBar.h"
#include <cstdlib>

EnemyReaper::EnemyReaper(unsigned int pos)
	: Enemy("∆нец",
		{ {Stat::HP, 90}, {Stat::ATK, 35}, {Stat::DEF, 20}, {Stat::AGI, 5} },
		"data/reaper.png", 140, sf::milliseconds(150),
		{ {BattleAnimationState::Idle, 8},
		  {BattleAnimationState::Attack, 10},
		  {BattleAnimationState::TakeHit, 3},
		  {BattleAnimationState::Death, 10} }, 4, 750.f)
{
	animationPassedTime = sf::milliseconds(std::rand() % 150);
	animationCurFrame = std::rand() % 8;
	float ww = 1920.f, wh = 1080.f;
	switch (pos)
	{
	case 1:
		position = sf::Vector2f(ww, wh/2-size/2);
		break;
	case 2:
		position = sf::Vector2f(ww-425, -30.f);
		break;
	case 3:
		position = sf::Vector2f(ww-425, wh-size+30);
		break;
	default:
		throw new std::exception();
	}
	position *= GameManager::ResCoefX();
}

sf::Vector2f EnemyReaper::GetHealthBarPos()
{
	sf::Vector2f hbs = GuiProgressBar::GetHealthBarSize();
	float w = hbs.x, h = hbs.y;
	return sf::Vector2f(position.x-size+size/2-w/2, position.y+h*5);
}

sf::FloatRect EnemyReaper::GetClickHitbox()
{
	sf::Vector2f pos = sf::Vector2f(position.x - size, position.y);
	const float coef = 0.6f;
	return sf::FloatRect(
		sf::Vector2f(pos.x+size/2*(1-coef), pos.y+size/2*(1-coef)),
		sf::Vector2f(size*coef, size*coef));
}

unsigned int EnemyReaper::DropExp()
{
	return 200;
}

std::vector<Item*> EnemyReaper::DropLoot()
{
	return {Item::Create(16, 1), Item::Create(7, 5)};
}
