#include "EnemyGoblin.h"
#include "../GameManager.h"
#include "../Gui/GuiProgressBar.h"
#include <cstdlib>

EnemyGoblin::EnemyGoblin(unsigned int pos)
	: Enemy("Гоблин",
		{ {Stat::HP, 40}, {Stat::ATK, 20}, {Stat::DEF, 0}, {Stat::AGI, 0} },
		"data/goblin.png", 150, sf::milliseconds(150),
		{ {BattleAnimationState::Idle, 4},
		  {BattleAnimationState::Attack, 8},
		  {BattleAnimationState::TakeHit, 4},
		  {BattleAnimationState::Death, 4} }, 6, 750.f)
{
	animationPassedTime = sf::milliseconds(std::rand() % 150);
	animationCurFrame = std::rand() % 8;
	float ww = (float)GameManager::WindowWidth(),
		wh = (float)GameManager::WindowHeight();
	switch (pos)
	{
	case 1:
		position = sf::Vector2f(ww + 129, wh/2 - size/2);
		break;
	case 2:
		position = sf::Vector2f(ww - 250, -150.f);
		break;
	case 3:
		position = sf::Vector2f(ww - 250, wh - size + 150);
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
	return sf::Vector2f(position.x - size + size/2 - w/2, position.y + h*10);
}

sf::FloatRect EnemyGoblin::GetClickHitbox()
{
	sf::Vector2f pos = sf::Vector2f(position.x - size, position.y);
	const float coef = 0.5f;
	return sf::FloatRect(
		sf::Vector2f(pos.x + size/2*(1-coef), pos.y + size/2*(1-coef)),
		sf::Vector2f(size*coef, size*coef));
}

bool EnemyGoblin::FinishedActionAnimation()
{
	return finishedAttack;
}