#include "Entity.h"

Entity::Entity(unsigned int hitFrameNum)
	: battleAnimationState(BattleAnimationState::Idle),
	hp(0), hitFrameNumber(hitFrameNum)
{
	animationCurFrame = 0;
	animationPassedTime = sf::Time::Zero;
}

int &Entity::GetHP()
{
	return hp;
}

bool Entity::IsHitFrame()
{
	return battleAnimationState == BattleAnimationState::Attack
		&& animationCurFrame == hitFrameNumber;
}

bool Entity::IsAlive()
{
	return hp > 0;
}

bool Entity::IsOut()
{
	return !IsAlive() && FinishedDeathAnimation();
}