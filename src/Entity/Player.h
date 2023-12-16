#pragma once

#include "Entity.h"
#include "../Item/Item.h"
#include <map>

enum class PlayerDirection
	{ Left, Right };

class Player : public Entity
{
public:
	Player(sf::Vector2u startPos,
		PlayerDirection startDir);
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;
	sf::Vector2f GetHealthBarPos() override;
	unsigned int Attack() override;
	bool FinishedActionAnimation() override;
	bool FinishedHitAnimation() override;
	bool FinishedDeathAnimation() override;
	void TakeHit(unsigned int damage) override;

	static sf::Vector2f GetPos();
	static float GetSize();
	static Item *GetItem(unsigned int pos);
	static bool HasItem(ItemTemplate *itemTemplate);
	static void SetItem(unsigned int pos, Item *item);
	static void InBattle(bool set);
	static std::map<Stat, unsigned int> GetStats();
	static sf::Vector2f GetScreenPos();
	static float GetScrenSize();
	static unsigned int GetMaxHP();
	static void Heal(unsigned int healing);
	static Player *Get();

private:
	void UpdateInGame(sf::Time deltaTime);
	void UpdateInBattle(sf::Time deltaTime);
	void RenderInGame(sf::RenderWindow*);
	void RenderInBattle(sf::RenderWindow*);
	void TryMove(float deltaX, float deltaY);
	sf::Vector2f GetFixedPos(float deltaX, float deltaY,
		sf::Vector2f playerPos, float playerSize,
		float otherX, float otherY);
	float GenerateRequiredDistance();

	bool isInBattle;
	sf::Vector2f position;
	PlayerDirection direction;
	PlayerAnimationState animationState;
	std::map<PlayerAnimationState, unsigned int> numOfFrames;
	std::map<BattleAnimationState, unsigned int> numOfBattleFrames;
	std::map<Stat, unsigned int> stats;
	Item *inventory[20] = {};
	float walkedDistance, requiredDistance;

	static inline Player *currentPlayer;
	static inline const float speed = 300.f,
		sprintCoef = 1.5f, sizeCoef = 0.9f;
};