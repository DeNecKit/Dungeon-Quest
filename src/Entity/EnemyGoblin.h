#pragma once

#include "Enemy.h"

class EnemyGoblin final : public Enemy
{
public:
	EnemyGoblin(unsigned int pos);
	sf::Vector2f GetHealthBarPos() override;
	sf::FloatRect GetClickHitbox() override;
	bool FinishedActionAnimation() override;
};