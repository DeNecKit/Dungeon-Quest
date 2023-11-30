#include "Entity.h"

Entity::Entity(sf::Time animDeltaTime)
	: battleAnimationState(BattleAnimationState::Idle)
{
	animationCurFrame = 0;
	animationPassedTime = sf::Time::Zero;
	animationDeltaTime = animDeltaTime;
}

void Entity::Update(sf::Time deltaTime) {}