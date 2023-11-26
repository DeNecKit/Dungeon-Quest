#pragma once

#include <SFML/Graphics.hpp>

enum class BattleAnimationState
	{ Idle, Attack, TakeHit, Death };

enum class PlayerAnimationState
	{ Idle, Walking };

class Animatable
{
public:
protected:
	sf::Texture animationTileset;
	sf::Time animationDeltaTime, animationPassedTime;
	unsigned int animationCurFrame;
};