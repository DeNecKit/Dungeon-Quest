#pragma once

#include "Entity.h"
#include "../Item/Item.h"
#include <map>
#include <vector>

class Enemy : public Entity
{
public:
	Enemy(const sf::String &name,
		std::map<Stat, unsigned int> stats, const char *tilesetPath,
		unsigned int texSize, sf::Time animDeltaTime,
		std::map<BattleAnimationState, unsigned int> numOfFrames,
		unsigned int hitFrameNum, float size);
	~Enemy();
	void ProcessEvent(const sf::Event&);
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;
	unsigned int Attack() override;
	void TakeHit(unsigned int damage) override;
	std::map<Stat, unsigned int> GetStats();
	virtual sf::FloatRect GetClickHitbox() = 0;
	virtual unsigned int DropExp() = 0;
	virtual std::vector<Item*> DropLoot() = 0;

protected:
	const sf::String &name;
	std::map<Stat, unsigned int> stats;
	unsigned int textureSize;
	std::map<BattleAnimationState, unsigned int> numOfFrames;
	sf::Vector2f position;
	float size;
	sf::RectangleShape *targetHover;
	bool finishedAttack, finishedHit, finishedDeath;
};