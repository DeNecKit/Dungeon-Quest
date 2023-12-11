#pragma once

#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include <vector>

class Battle
{
public:
	Battle(Player *player, std::vector<Enemy*> enemies);
	~Battle();
	void ProcessEvent(const sf::Event&);
	void Update(sf::Time deltaTime);
	void Render(sf::RenderWindow*);
	
	static void Start(Player *player, std::vector<Enemy*> enemies);
	static void End();
	static Battle *Get();

private:
	Player *player;
	std::vector<Enemy*> enemies;

	static inline Battle *instance = nullptr;
};