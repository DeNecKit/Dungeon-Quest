#include "Entity.h"

Entity::Entity(unsigned int hitFrameNum)
	: battleAnimationState(BattleAnimationState::Idle),
	hp(0), hitFrameNumber(hitFrameNum)
{
	animationCurFrame = 0;
	animationPassedTime = sf::Time::Zero;
}

unsigned int &Entity::GetHP()
{
	return hp;
}

bool Entity::IsHitFrame()
{
	return animationCurFrame == hitFrameNumber;
}