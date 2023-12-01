#pragma once

#include "Animatable.h"

class Entity : public Animatable
{
public:
	Entity(sf::Time animDeltaTime);
	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Render(sf::RenderWindow*) = 0;

protected:
	BattleAnimationState battleAnimationState;
};