#pragma once

#include "Entity.h"
#include <map>

enum class PlayerDirection
	{ Left, Right, Up, Down };

class Player : public Entity
{
public:
	Player(sf::Vector2u startPos,
		PlayerDirection startDir, sf::Time animDeltaTime);
	sf::Vector2f GetPos();
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow *window) override;

private:
	void TryMove(float deltaX, float deltaY);

	const float speed = 300.f, sizeCoef = 0.9f;
	bool isInBattle;
	sf::Vector2f position;
	PlayerDirection direction;
	PlayerAnimationState animationState;
	std::map<PlayerAnimationState, unsigned int> numOfFrames;
	std::map<BattleAnimationState, unsigned int> numOfBattleFrames;
};