#include "EnemyGoblin.h"
#include "../Gui/GuiProgressBar.h"
#include <cstdlib>

EnemyGoblin::EnemyGoblin(unsigned int pos)
	: Enemy("Гоблин",
		{ {Stat::HP, 30}, {Stat::ATK, 17}, {Stat::DEF, 5}, {Stat::AGI, 5} },
		"data/goblin.png", 150, sf::milliseconds(150),
		{ {BattleAnimationState::Idle, 4},
		  {BattleAnimationState::Attack, 8},
		  {BattleAnimationState::TakeHit, 4},
		  {BattleAnimationState::Death, 4} }, 6, 750.f)
{
	animationPassedTime = sf::milliseconds(std::rand() % 150);
	animationCurFrame = std::rand() % 4;
	float ww = 1920.f, wh = 1080.f;
	switch (pos)
	{
	case 1:
		position = sf::Vector2f(ww + 129, wh/2 - size/2);
		break;
	case 2:
		position = sf::Vector2f(ww - 300, -150.f);
		break;
	case 3:
		position = sf::Vector2f(ww - 300, wh - size + 150);
		break;
	default:
		throw new std::exception();
	}
	position *= GameManager::ResCoefX();
}

sf::Vector2f EnemyGoblin::GetHealthBarPos()
{
	sf::Vector2f hbs = GuiProgressBar::GetHealthBarSize();
	float w = hbs.x, h = hbs.y;
	return sf::Vector2f(position.x - size + size/2 - w/2, position.y + h*9);
}

sf::FloatRect EnemyGoblin::GetClickHitbox()
{
	sf::Vector2f pos = sf::Vector2f(position.x - size, position.y);
	const float coef = 0.5f;
	return sf::FloatRect(
		sf::Vector2f(pos.x + size/2*(1-coef), pos.y + size/2*(1-coef)),
		sf::Vector2f(size*coef, size*coef));
}

unsigned int EnemyGoblin::DropExp()
{
	return std::rand() % 11 + 5;
}

std::vector<Item*> EnemyGoblin::DropLoot()
{
	static bool swordDropped = false;
	std::vector<Item*> res;
	if (std::rand() % 5 > 0)
		res.push_back(Item::Create(7, 1));
	if (!swordDropped && std::rand() % 20 == 0)
	{
		res.push_back(Item::Create(9, 1));
		swordDropped = true;
	}
	return res;
}