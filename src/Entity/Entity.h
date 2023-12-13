#pragma once

#include "../Animatable.h"

enum class Stat { HP, ATK, DEF, AGI };

class Entity : public Animatable
{
public:
	Entity(unsigned int hitFrameNum);
	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Render(sf::RenderWindow*) = 0;
	virtual sf::Vector2f GetHealthBarPos() = 0;
	virtual unsigned int Attack() = 0;
	virtual bool FinishedActionAnimation() = 0;
	virtual bool FinishedHitAnimation() = 0;
	virtual bool FinishedDeathAnimation() = 0;
	virtual void TakeHit(unsigned int damage) = 0;
	int &GetHP();
	bool IsHitFrame();
	bool IsAlive();
	bool IsOut();

protected:
	int hp;
	BattleAnimationState battleAnimationState;
	unsigned int hitFrameNumber;
};