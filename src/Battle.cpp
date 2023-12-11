#include "Battle.h"
#include "SceneManager.h"
#include "Scene/SceneBattle.h"
#include "Scene/SceneGame.h"

Battle::Battle(Player* player, std::vector<Enemy*> enemies)
	: player(player), enemies(enemies) {}

Battle::~Battle()
{
	for (Enemy *enemy : enemies)
		delete enemy;
}

void Battle::ProcessEvent(const sf::Event& event)
{
}

void Battle::Update(sf::Time deltaTime)
{
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
	Player::InBattle(true);
	SceneManager::ChangeScene<SceneBattle>();
}

void Battle::End()
{
	delete instance;
	instance = nullptr;
	Player::InBattle(false);
	SceneManager::ChangeScene<SceneGame>();
}

Battle* Battle::Get()
{
	return instance;
}