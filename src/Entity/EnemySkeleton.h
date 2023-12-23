#pragma once

#include "Enemy.h"

class EnemySkeleton final : public Enemy
{
public:
	EnemySkeleton(unsigned int pos);
	sf::Vector2f GetHealthBarPos() override;
	sf::FloatRect GetClickHitbox() override;
	unsigned int DropExp() override;
	std::vector<Item*> DropLoot() override;
};