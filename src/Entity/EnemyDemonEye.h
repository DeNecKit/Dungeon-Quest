#pragma once

#include "Enemy.h"

class EnemyDemonEye final : public Enemy
{
public:
	EnemyDemonEye(unsigned int pos);
	sf::Vector2f GetHealthBarPos() override;
	sf::FloatRect GetClickHitbox() override;
	unsigned int DropExp() override;
	std::vector<Item*> DropLoot() override;
};