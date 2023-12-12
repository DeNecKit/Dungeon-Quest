#include "Battle.h"
#include "SceneManager.h"
#include "Scene/SceneBattle.h"
#include "Scene/SceneGame.h"


Battle::Battle(Player* player, std::vector<Enemy*> enemies)
	: player(player), enemies(enemies), target(enemies[0]),
	chosenAction(TurnAction::None), currentStage(TurnStage::Waiting),
	timer(sf::Time::Zero), turnMaker(Player::Get()), curEnemyIndex(0) {}

Battle::~Battle()
{
	for (Enemy *enemy : enemies)
		delete enemy;
}

void Battle::Update(sf::Time deltaTime)
{
	switch (currentStage)
	{
	case TurnStage::Waiting:
		if (!IsPlayerTurn()) MakeTurn(TurnAction::Attack);
		break;
	case TurnStage::Action:
		if (!turnMaker->FinishedActionAnimation()) break;
		timer += deltaTime;
		if (timer < sf::milliseconds(500)) break;
		currentStage = TurnStage::Waiting;
		timer = sf::Time::Zero;
		if (IsPlayerTurn())
		{
			curEnemyIndex = 0;
			turnMaker = Battle::GetEnemies()[0];
		} else if (++curEnemyIndex == Battle::GetEnemies().size())
			turnMaker = Player::Get();
		else turnMaker = Battle::GetEnemies()[curEnemyIndex];
		break;
	}
	player->Update(deltaTime);
	for (Enemy *enemy : enemies)
		enemy->Update(deltaTime);
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
	delete instance;
	instance = nullptr;
	SceneManager::ChangeScene<SceneGame>();
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

Battle* Battle::Get()
{
	return instance;
}