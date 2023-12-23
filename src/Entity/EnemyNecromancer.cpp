#include "EnemyNecromancer.h"
#include "../Gui/GuiProgressBar.h"
#include <cstdlib>

EnemyNecromancer::EnemyNecromancer(unsigned int pos)
	: Enemy("Некромант",
		{ {Stat::HP, 250}, {Stat::ATK, 100}, {Stat::DEF, 35}, {Stat::AGI, 15} },
		"data/necromancer.png", 160, sf::milliseconds(150),
		{ {BattleAnimationState::Idle, 8},
		  {BattleAnimationState::Attack, 13},
		  {BattleAnimationState::TakeHit, 5},
		  {BattleAnimationState::Death, 10} }, 8, 850.f)
{
	animationPassedTime = sf::milliseconds(std::rand() % 150);
	animationCurFrame = std::rand() % 8;
	float ww = 1920.f, wh = 1080.f;
	if (pos != 1) throw new std::exception();
	position = sf::Vector2f(ww+150, 100.f);
	position *= GameManager::ResCoefX();
}

sf::Vector2f EnemyNecromancer::GetHealthBarPos()
{
	sf::Vector2f hbs = GuiProgressBar::GetHealthBarSize();
	float w = hbs.x, h = hbs.y;
	return sf::Vector2f(position.x-size+size/2-w/2, position.y+h*9);
}

sf::FloatRect EnemyNecromancer::GetClickHitbox()
{
	sf::Vector2f pos = sf::Vector2f(position.x - size, position.y);
	const float coef = 0.5f;
	return sf::FloatRect(
		sf::Vector2f(pos.x + size/2*(1-coef), pos.y + size/2*(1-coef)),
		sf::Vector2f(size*coef, size*coef));
}

unsigned int EnemyNecromancer::DropExp()
{
	return 500;
}

std::vector<Item*> EnemyNecromancer::DropLoot()
{
	return {Item::Create(19, 1), Item::Create(25, 5)};
}
