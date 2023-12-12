#include "SceneBattle.h"
#include "../SceneManager.h"
#include "SceneGame.h"
#include "../Battle.h"
#include "../Gui/GuiButton.h"
#include "../GameManager.h"
#include "../Entity/Player.h"

void SetTargetRect(sf::RectangleShape &targetRect)
{
	sf::FloatRect td = Battle::Get()->target->GetClickHitbox();
	float tw = td.width*0.5f, th = 15.f,
		tx = td.left + td.width/2 - tw/2, ty = td.top + td.height - th*2;
	targetRect = sf::RectangleShape(sf::Vector2f(tw, th));
	targetRect.setPosition(tx, ty);
	targetRect.setFillColor(sf::Color::Green);
}

SceneBattle::SceneBattle()
	: pauseMenu(nullptr), inventoryGui(nullptr), lastTarget(Battle::Get()->target)
{
	Player::InBattle(true);
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
		L"Атака", 24, [](const sf::Event&) { Battle::MakeTurn(TurnAction::Attack); }));
	actionsMenu->Append(new GuiButton(sf::FloatRect(x+d*2+bw, y+d, bw, bh),
		L"Предмет", 24, [](const sf::Event&) {}));
	actionsMenu->Append(new GuiButton(sf::FloatRect(x+d*3+bw*2, y+d, bw, bh),
		L"Побег", 24, [](const sf::Event&) { Battle::End(); }));
	SetTargetRect(targetRect);
}

SceneBattle::~SceneBattle()
{
	delete playerHealthBar;
	for (GuiProgressBar *enemyBar : enemiesHealthBar)
		delete enemyBar;
	delete actionsMenu;
	Player::InBattle(false);
}

void SceneBattle::ProcessEvent(const sf::Event &event)
{
	if (Battle::IsPlayerTurn()) actionsMenu->ProcessEvent(event);
	if (Battle::Get() == nullptr) return;
	for (Enemy *enemy : Battle::GetEnemies())
		enemy->ProcessEvent(event);
}

void SceneBattle::Update(sf::Time deltaTime)
{
	if (Battle::Get() == nullptr) return;
	Battle::Get()->Update(deltaTime);
	playerHealthBar->Update(deltaTime);
	for (GuiProgressBar *enemyBar : enemiesHealthBar)
		enemyBar->Update(deltaTime);
	for (Gui *gui : actionsMenu->GetChildren())
	{
		GuiButton *btn = dynamic_cast<GuiButton*>(gui);
		btn->SetEnabled(Battle::IsPlayerTurn() &&
			Battle::GetStage() == TurnStage::Waiting);
	}
	if (Battle::IsPlayerTurn()) actionsMenu->Update(deltaTime);
	if (lastTarget != Battle::Get()->target)
	{
		SetTargetRect(targetRect);
		lastTarget = Battle::Get()->target;
	}
}

void SceneBattle::RenderGUI(sf::RenderWindow *window)
{
	if (Battle::Get() == nullptr) return;
	playerHealthBar->Render(window);
	for (GuiProgressBar *enemyBar : enemiesHealthBar)
		enemyBar->Render(window);
	actionsMenu->Render(window);
	window->draw(targetRect);
	for (Enemy *enemy : Battle::GetEnemies())
		enemy->Render(window);
}

void SceneBattle::RenderSFML(sf::RenderWindow *window)
{
	if (Battle::Get() == nullptr) return;
	window->clear(sf::Color(58, 51, 62));
	Battle::Get()->Render(window);
}