#include "SceneBattle.h"
#include "../SceneManager.h"
#include "SceneGame.h"
#include "../Battle.h"
#include "../Gui/GuiButton.h"
#include "../GameManager.h"
#include "../Entity/Player.h"

void setTargetRect(sf::RectangleShape &targetRect)
{
	sf::FloatRect hitbox = Battle::Get()->target->GetClickHitbox();
	targetRect = sf::RectangleShape(hitbox.getSize());
	targetRect.setPosition(hitbox.getPosition());
	targetRect.setFillColor(sf::Color::Transparent);
	targetRect.setOutlineThickness(2.f);
	targetRect.setOutlineColor(sf::Color(0, 255, 0, 100));
}

SceneBattle::SceneBattle()
	: pauseMenu(nullptr), inventoryGui(nullptr), lastTarget(Battle::Get()->target)
{
	Player::InBattle(true);
	sf::Vector2f hbs = GuiProgressBar::GetHealthBarSize();
	playerHealthBar = new GuiProgressBar(
		sf::FloatRect(Player::Get()->GetHealthBarPos(), hbs), Gui::HealthBarFillColor,
		(unsigned int&)Player::Get()->GetHP(), Player::GetStats()[Stat::HP]);
	for (Enemy *enemy : Battle::GetEnemies())
		enemiesHealthBar.push_back(new GuiProgressBar(
		sf::FloatRect(enemy->GetHealthBarPos(), hbs), Gui::HealthBarFillColor,
			(unsigned int&)enemy->GetHP(), enemy->GetStats()[Stat::HP]));
	float bw = 250.f, bh = 75.f, d = 25.f, w = bw*3 + d*4, h = bh + d*2,
		x = d*3, y = GameManager::WindowHeight() - d*3 - h;
	actionsMenu = new GuiList(sf::FloatRect(x, y, w, h));
	actionsMenu->Append(new GuiButton(sf::FloatRect(x+d, y+d, bw, bh),
		L"Атака", 24, [](const sf::Event&) { Battle::MakeTurn(TurnAction::Attack); }));
	actionsMenu->Append(new GuiButton(sf::FloatRect(x+d*2+bw, y+d, bw, bh),
		L"Предмет", 24, [](const sf::Event&) {}));
	actionsMenu->Append(new GuiButton(sf::FloatRect(x+d*3+bw*2, y+d, bw, bh),
		L"Побег", 24, [](const sf::Event&) { Battle::End(); }));
	setTargetRect(targetRect);
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
		setTargetRect(targetRect);
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
}

void SceneBattle::RenderSFML(sf::RenderWindow *window)
{
	if (Battle::Get() == nullptr) return;
	window->clear(sf::Color(58, 51, 62));
	Battle::Get()->Render(window);
}