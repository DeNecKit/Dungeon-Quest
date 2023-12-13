#include "Battle.h"
#include "SceneManager.h"
#include "Scene/SceneBattle.h"
#include "Scene/SceneGame.h"
#include "Scene/SceneMainMenu.h"
#include <cstdlib>

Battle::Battle(Player* player, std::vector<Enemy*> enemies)
	: player(player), enemies(enemies), target(enemies[0]),
	chosenAction(TurnAction::None), currentStage(TurnStage::Waiting),
	timer(sf::Time::Zero), turnMaker(Player::Get()), curEnemyIndex(0),
	isVictory(false), isDefeat(false) {}

Battle::~Battle()
{
	for (Enemy *enemy : enemies)
		delete enemy;
}

void Battle::Update(sf::Time deltaTime)
{
	static bool turnMakerAttacked = false;
	Entity *defender = IsPlayerTurn()
		? dynamic_cast<Entity*>(target)
		: dynamic_cast<Entity*>(Player::Get());
	switch (currentStage)
	{
	case TurnStage::Waiting:
		if (!IsPlayerTurn()) MakeTurn(TurnAction::Attack);
		else
		{
			int i = 0;
			while (target->IsOut() && i < enemies.size())
				target = enemies[i++];
			if (target->IsOut())
				isVictory = true;
		}
		break;
	case TurnStage::Action:
		if (chosenAction == TurnAction::Flee)
			if (std::rand() % 2)
			{
				Battle::End();
				return;
			} else
			{
				SceneBattle::Message(L"Не удалось сбежать!");
				currentStage = TurnStage::Waiting;
				PlayerEndTurn();
			}
		else if (chosenAction == TurnAction::UseItem)
		{
			if (chosenItem == nullptr)
			{
				SceneBattle::ShowInventory(true);
			} else
			{
				// TODO
				chosenItem = nullptr;
				PlayerEndTurn();
				SceneBattle::ShowInventory(false);
			}
			currentStage = TurnStage::Waiting;
		}
		if (!turnMakerAttacked && turnMaker->IsHitFrame())
		{ 
			defender->TakeHit(turnMaker->Attack());
			turnMakerAttacked = true;
		}
		if (!turnMaker->FinishedActionAnimation()) break;
		if (!defender->FinishedHitAnimation()) break;
		if (!defender->IsAlive() && !defender->FinishedDeathAnimation()) break;
		timer += deltaTime;
		if (timer < sf::milliseconds(500)) break;
		currentStage = TurnStage::Waiting;
		timer = sf::Time::Zero;
		turnMakerAttacked = false;
		if (Player::Get()->IsOut()) isDefeat = true;
		do
			if (IsPlayerTurn())
			{
				curEnemyIndex = 0;
				turnMaker = enemies[0];
			} else if (++curEnemyIndex == enemies.size())
				turnMaker = Player::Get();
			else turnMaker = enemies[curEnemyIndex];
		while (turnMaker->IsOut());
		break;
	}
	player->Update(deltaTime);
	for (Enemy *enemy : enemies)
		if (!enemy->IsOut()) enemy->Update(deltaTime);
}

void Battle::Render(sf::RenderWindow* window)
{
	player->Render(window);
	for (Enemy *enemy : enemies)
		enemy->Render(window);
}

void Battle::Start(Player *player, std::vector<Enemy*> enemies)
{
	instance = new Battle(player, enemies);
	SceneManager::ChangeScene<SceneBattle>();
}

void Battle::End()
{
	if (instance->isDefeat) SceneManager::ChangeScene<SceneMainMenu>();
	else SceneManager::ChangeScene<SceneGame>();
	delete instance;
	instance = nullptr;
}

std::vector<Enemy*> Battle::GetEnemies()
{
	return instance->enemies;
}

bool Battle::IsPlayerTurn()
{
	return dynamic_cast<Player*>(instance->turnMaker);
}

void Battle::MakeTurn(TurnAction action)
{
	instance->chosenAction = action;
	instance->currentStage = TurnStage::Action;
}

TurnAction Battle::GetChosenAction()
{
	return instance->chosenAction;
}

TurnStage Battle::GetStage()
{
	return instance->currentStage;
}

Entity* Battle::GetTurnMaker()
{
	return instance->turnMaker;
}

void Battle::ChooseItem(Item *item)
{
	instance->chosenItem = item;
	MakeTurn(TurnAction::UseItem);
}

Battle* Battle::Get()
{
	return instance;
}

void Battle::PlayerEndTurn()
{
	curEnemyIndex = 0;
	turnMaker = enemies[0];
	while (turnMaker->IsOut())
		turnMaker = enemies[++curEnemyIndex];
}

bool Battle::IsVictory()
{
	return instance->isVictory;
}

bool Battle::IsDefeat()
{
	return instance->isDefeat;
}

bool Battle::IsEnd()
{
	return IsVictory() || IsDefeat();
}