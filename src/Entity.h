#pragma once

#include "Animatable.h"

enum class Stat { HP, ATK, DEF, AGI };

class Entity : public Animatable
{
public:
	Entity();
	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Render(sf::RenderWindow*) = 0;

protected:
	BattleAnimationState battleAnimationState;
};