#pragma once

#include "Enemy.h"

class EnemyGoblinKing : public Enemy
{
public:
	EnemyGoblinKing(unsigned int pos);
	sf::Vector2f GetHealthBarPos() override;
	sf::FloatRect GetClickHitbox() override;
	bool FinishedActionAnimation() override;
	bool FinishedHitAnimation() override;
	bool FinishedDeathAnimation() override;
	unsigned int DropExp() override;
	std::vector<Item*> DropLoot() override;
};