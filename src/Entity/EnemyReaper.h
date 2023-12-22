#pragma once

#include "Enemy.h"

class EnemyReaper : public Enemy
{
public:
	EnemyReaper(unsigned int pos);
	sf::Vector2f GetHealthBarPos() override;
	sf::FloatRect GetClickHitbox() override;
	unsigned int DropExp() override;
	std::vector<Item*> DropLoot() override;
};