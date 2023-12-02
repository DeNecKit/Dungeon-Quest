#include "Entity.h"

Entity::Entity()
	: battleAnimationState(BattleAnimationState::Idle)
{
	animationCurFrame = 0;
	animationPassedTime = sf::Time::Zero;
}