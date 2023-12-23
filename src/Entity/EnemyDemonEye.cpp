#include "EnemyDemonEye.h"
#include "../Gui/GuiProgressBar.h"
#include <cstdlib>

EnemyDemonEye::EnemyDemonEye(unsigned int pos)
	: Enemy("Демонический глаз",
		{ {Stat::HP, 70}, {Stat::ATK, 35}, {Stat::DEF, 5}, {Stat::AGI, 15} },
		"data/demon-eye.png", 150, sf::milliseconds(150),
		{ {BattleAnimationState::Idle, 8},
		  {BattleAnimationState::Attack, 8},
		  {BattleAnimationState::TakeHit, 4},
		  {BattleAnimationState::Death, 4} }, 6, 500.f)
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

sf::Vector2f EnemyDemonEye::GetHealthBarPos()
{
	sf::Vector2f hbs = GuiProgressBar::GetHealthBarSize();
	float w = hbs.x, h = hbs.y;
	return sf::Vector2f(position.x-size+size/2-w/2, position.y+h*5);
}

sf::FloatRect EnemyDemonEye::GetClickHitbox()
{
	sf::Vector2f pos = sf::Vector2f(position.x - size, position.y);
	const float coef = 0.6f;
	return sf::FloatRect(
		sf::Vector2f(pos.x + size/2*(1-coef), pos.y + size/2*(1-coef)),
		sf::Vector2f(size*coef, size*coef));
}

unsigned int EnemyDemonEye::DropExp()
{
	return std::rand() % 11 + 25;
}

std::vector<Item*> EnemyDemonEye::DropLoot()
{
	static bool swordDropped = false;
	std::vector<Item*> res;
	if (std::rand() % 2)
		res.push_back(Item::Create(7, std::rand() % 3 + 1));
	if (std::rand() % 2)
		res.push_back(Item::Create(24, 1));
	if (!swordDropped && std::rand() % 20 == 0)
	{
		res.push_back(Item::Create(15, 1));
		swordDropped = true;
	}
	return res;
}
