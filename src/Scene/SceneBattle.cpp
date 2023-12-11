#include "SceneBattle.h"
#include "../SceneManager.h"
#include "SceneGame.h"
#include "../Battle.h"
#include "../Gui/GuiButton.h"
#include "../GameManager.h"

SceneBattle::SceneBattle()
{
	sf::Vector2f hbs = GuiProgressBar::GetHealthBarSize();
	playerHealthBar = new GuiProgressBar(
		sf::FloatRect(Player::Get()->GetHealthBarPos(), hbs), sf::Color::Red,
		Player::Get()->GetHP(), Player::GetStats()[Stat::HP]);
	for (Enemy *enemy : Battle::GetEnemies())
		enemiesHealthBar.push_back(new GuiProgressBar(
		sf::FloatRect(enemy->GetHealthBarPos(), hbs), sf::Color::Red,
			enemy->GetHP(), enemy->GetStats()[Stat::HP]));
	float bw = 250.f, bh = 75.f, d = 25.f, w = bw*3 + d*4, h = bh + d*2,
		x = d*3, y = GameManager::WindowHeight() - d*3 - h;
	actionsMenu = new GuiList(sf::FloatRect(x, y, w, h));
	actionsMenu->Append(new GuiButton(sf::FloatRect(x+d, y+d, bw, bh),
		L"Атака", 24, [](const sf::Event&) {}));
	actionsMenu->Append(new GuiButton(sf::FloatRect(x+d*2+bw, y+d, bw, bh),
		L"Предмет", 24, [](const sf::Event&) {}));
	actionsMenu->Append(new GuiButton(sf::FloatRect(x+d*3+bw*2, y+d, bw, bh),
		L"Побег", 24, [](const sf::Event&) { Battle::End(); }));
}

SceneBattle::~SceneBattle()
{
	delete playerHealthBar;
	for (GuiProgressBar *enemyBar : enemiesHealthBar)
		delete enemyBar;
	delete actionsMenu;
}

void SceneBattle::ProcessEvent(const sf::Event &event)
{
	if (Battle::Get() == nullptr) return;
	if (Battle::IsPlayerTurn()) actionsMenu->ProcessEvent(event);
}

void SceneBattle::Update(sf::Time deltaTime)
{
	if (Battle::Get() == nullptr) return;
	Battle::Get()->Update(deltaTime);
	playerHealthBar->Update(deltaTime);
	for (GuiProgressBar *enemyBar : enemiesHealthBar)
		enemyBar->Update(deltaTime);
	if (Battle::IsPlayerTurn()) actionsMenu->Update(deltaTime);
}

void SceneBattle::RenderGUI(sf::RenderWindow *window)
{
	if (Battle::Get() == nullptr) return;
	playerHealthBar->Render(window);
	for (GuiProgressBar *enemyBar : enemiesHealthBar)
		enemyBar->Render(window);
	if (Battle::IsPlayerTurn()) actionsMenu->Render(window);
}

void SceneBattle::RenderSFML(sf::RenderWindow *window)
{
	if (Battle::Get() == nullptr) return;
	Battle::Get()->Render(window);
}