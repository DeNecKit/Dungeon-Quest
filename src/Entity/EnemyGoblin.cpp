#include "EnemyGoblin.h"

EnemyGoblin::EnemyGoblin()
	: Enemy("Гоблин", { {Stat::HP, 40}, {Stat::ATK, 20},
		{Stat::DEF, 0}, {Stat::AGI, 0} },
		"data/goblin.png", 150, sf::milliseconds(150),
		{ {BattleAnimationState::Idle, 4},
		  {BattleAnimationState::Attack, 8},
		  {BattleAnimationState::TakeHit, 4},
		  {BattleAnimationState::Death, 4} }) {}