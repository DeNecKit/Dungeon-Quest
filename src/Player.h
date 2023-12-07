#pragma once

#include "Entity.h"
#include "Item/Item.h"
#include <map>

enum class PlayerDirection
	{ Left, Right };

class Player : public Entity
{
public:
	Player(sf::Vector2u startPos,
		PlayerDirection startDir);
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow *window) override;

	static sf::Vector2f GetPos();
	static float GetSize();
	static Item *GetItemAt(unsigned int pos);

private:
	void TryMove(float deltaX, float deltaY);
	sf::Vector2f GetFixedPos(float deltaX, float deltaY,
		sf::Vector2f playerPos, float playerSize,
		float otherX, float otherY);

	bool isInBattle;
	sf::Vector2f position;
	PlayerDirection direction;
	PlayerAnimationState animationState;
	std::map<PlayerAnimationState, unsigned int> numOfFrames;
	std::map<BattleAnimationState, unsigned int> numOfBattleFrames;
	Item *inventory[20] = {};

	static inline Player *currentPlayer;
	static inline const float speed = 300.f,
		sprintCoef = 1.5f, sizeCoef = 0.9f;
};