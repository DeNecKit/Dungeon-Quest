#pragma once

#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include "Item/Item.h"
#include <vector>

enum class TurnAction { None, Attack, UseItem, Flee };
enum class TurnStage { Waiting, Action };

class Battle
{
public:
	Battle(Player *player, std::vector<Enemy*> enemies);
	~Battle();
	void Update(sf::Time deltaTime);
	void Render(sf::RenderWindow*);
	
	Enemy *target;

	static void Start(Player *player, std::vector<Enemy*> enemies);
	static void End();
	static std::vector<Enemy*> GetEnemies();
	static bool IsPlayerTurn();
	static void MakeTurn(TurnAction action);
	static TurnAction GetChosenAction();
	static TurnStage GetStage();
	static Entity *GetTurnMaker();
	static void ChooseItem(Item *item);
	static bool IsVictory();
	static bool IsDefeat();
	static bool IsEnd();
	static Battle *Get();

private:
	void PlayerEndTurn();

	Player *player;
	std::vector<Enemy*> enemies;
	TurnAction chosenAction;
	TurnStage currentStage;
	sf::Time timer;
	Entity *turnMaker;
	unsigned int curEnemyIndex;
	bool isVictory, isDefeat;
	Item *chosenItem;

	static inline Battle *instance = nullptr;
};