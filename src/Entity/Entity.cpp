#include "Entity.h"

Entity::Entity()
	: battleAnimationState(BattleAnimationState::Idle), hp(0)
{
	animationCurFrame = 0;
	animationPassedTime = sf::Time::Zero;
}

unsigned int &Entity::GetHP()
{
	return hp;
}