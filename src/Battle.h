#pragma once

#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include <vector>

enum class Turn { Player, Enemy };

class Battle
{
public:
	Battle(Player *player, std::vector<Enemy*> enemies);
	~Battle();
	void Update(sf::Time deltaTime);
	void Render(sf::RenderWindow*);
	
	static void Start(Player *player, std::vector<Enemy*> enemies);
	static void End();
	static std::vector<Enemy*> GetEnemies();
	static bool IsPlayerTurn();
	static Battle *Get();

private:
	Player *player;
	std::vector<Enemy*> enemies;
	Turn turn;

	static inline Battle *instance = nullptr;
};