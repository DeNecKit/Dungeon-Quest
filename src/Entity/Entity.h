#pragma once

#include "../Animatable.h"

enum class Stat { HP, ATK, DEF, AGI };

class Entity : public Animatable
{
public:
	Entity();
	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Render(sf::RenderWindow*) = 0;
	virtual sf::Vector2f GetHealthBarPos() = 0;
	virtual unsigned int Attack() = 0;
	unsigned int &GetHP();

protected:
	unsigned int hp;
	BattleAnimationState battleAnimationState;
};