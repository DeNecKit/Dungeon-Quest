#include "SceneBattle.h"
#include "../SceneManager.h"
#include "SceneGame.h"
#include "../Battle.h"

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
}

SceneBattle::~SceneBattle()
{
	delete playerHealthBar;
	for (GuiProgressBar *enemyBar : enemiesHealthBar)
		delete enemyBar;
}

void SceneBattle::ProcessEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::Escape)
		Battle::End();
	else Battle::Get()->ProcessEvent(event);
}

void SceneBattle::Update(sf::Time deltaTime)
{
	Battle::Get()->Update(deltaTime);
	playerHealthBar->Update(deltaTime);
	for (GuiProgressBar *enemyBar : enemiesHealthBar)
		enemyBar->Update(deltaTime);
}

void SceneBattle::RenderGUI(sf::RenderWindow *window)
{
	playerHealthBar->Render(window);
	for (GuiProgressBar *enemyBar : enemiesHealthBar)
		enemyBar->Render(window);
}

void SceneBattle::RenderSFML(sf::RenderWindow *window)
{
	Battle::Get()->Render(window);
}