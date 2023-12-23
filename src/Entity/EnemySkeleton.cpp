#include "EnemySkeleton.h"
#include "../Gui/GuiProgressBar.h"
#include <cstdlib>

EnemySkeleton::EnemySkeleton(unsigned int pos)
	: Enemy("Скелет",
		{ {Stat::HP, 95}, {Stat::ATK, 50}, {Stat::DEF, 20}, {Stat::AGI, 10} },
		"data/skeleton.png", 150, sf::milliseconds(150),
		{ {BattleAnimationState::Idle, 4},
		  {BattleAnimationState::Attack, 8},
		  {BattleAnimationState::TakeHit, 4},
		  {BattleAnimationState::Death, 4} }, 6, 600.f)
{
	animationPassedTime = sf::milliseconds(std::rand() % 150);
	animationCurFrame = std::rand() % 4;
	float ww = 1920.f, wh = 1080.f;
	switch (pos)
	{
	case 1:
		position = sf::Vector2f(ww+60, wh/2-size/2+40);
		break;
	case 2:
		position = sf::Vector2f(ww-425, -50.f);
		break;
	case 3:
		position = sf::Vector2f(ww-425, wh-size+110);
		break;
	default:
		throw new std::exception();
	}
	position *= GameManager::ResCoefX();
}

sf::Vector2f EnemySkeleton::GetHealthBarPos()
{
	sf::Vector2f hbs = GuiProgressBar::GetHealthBarSize();
	float w = hbs.x, h = hbs.y;
	return sf::Vector2f(position.x-size+size/2-w/2, position.y+h*4);
}

sf::FloatRect EnemySkeleton::GetClickHitbox()
{
	sf::Vector2f pos = sf::Vector2f(position.x - size, position.y);
	const float coef = 0.6f;
	return sf::FloatRect(
		sf::Vector2f(pos.x+size/2*(1-coef), pos.y+size/2*(1-coef)-30),
		sf::Vector2f(size*coef, size*coef));
}

unsigned int EnemySkeleton::DropExp()
{
	return std::rand() % 51 + 75;
}

std::vector<Item*> EnemySkeleton::DropLoot()
{
	static bool swordDropped = false;
	std::vector<Item*> res;
	if (std::rand() % 2)
		res.push_back(Item::Create(24, std::rand() % 5 + 2));
	if (std::rand() % 2)
		res.push_back(Item::Create(25, 1));
	if (!swordDropped && std::rand() % 20 == 0)
	{
		res.push_back(Item::Create(18, 1));
		swordDropped = true;
	}
	return res;
}
