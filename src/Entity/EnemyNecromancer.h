#pragma once

#include "Enemy.h"

class EnemyNecromancer final : public Enemy
{
public:
	EnemyNecromancer(unsigned int pos);
	sf::Vector2f GetHealthBarPos() override;
	sf::FloatRect GetClickHitbox() override;
	unsigned int DropExp() override;
	std::vector<Item*> DropLoot() override;
};