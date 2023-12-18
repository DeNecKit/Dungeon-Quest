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
	Battle(Player *player,
		std::vector<Enemy*> enemies, bool canEscape);
	~Battle();
	void Update(sf::Time deltaTime);
	void Render(sf::RenderWindow*);
	
	Enemy *target;

	static void Start(Player *player,
		std::vector<Enemy*> enemies, bool canEscape = true);
	static void End();
	static std::vector<Enemy*> GetEnemies();
	static bool IsPlayerTurn();
	static void MakeTurn(TurnAction action);
	static void SetTurnStage(TurnStage turnStage);
	static TurnAction GetChosenAction();
	static TurnStage GetStage();
	static Entity *GetTurnMaker();
	static void ChooseItem(Item *item);
	static bool CanEscape();
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
	bool canEscape;

	static inline Battle *instance = nullptr;
};