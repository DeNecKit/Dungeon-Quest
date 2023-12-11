#pragma once

#include "Entity.h"
#include <map>

class Enemy : public Entity
{
public:
	Enemy(const sf::String &name,
		std::map<Stat, unsigned int> stats, const char *tilesetPath,
		unsigned int texSize, sf::Time animDeltaTime,
		std::map<BattleAnimationState, unsigned int> numOfFrames);
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;
	unsigned int Attack() override;

private:
	const sf::String &name;
	std::map<Stat, unsigned int> stats;
	unsigned int textureSize;
	std::map<BattleAnimationState, unsigned int> numOfFrames;
};