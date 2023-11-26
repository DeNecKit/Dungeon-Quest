#include "SceneGame.h"
#include "SceneManager.h"
#include "SceneMainMenu.h"

SceneGame::SceneGame() : level(Level::Level1()) {}

void SceneGame::ProcessEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed
		&& event.key.code == sf::Keyboard::Escape)
		SceneManager::ChangeScene<SceneMainMenu>();
	level.ProcessEvent(event);
}

void SceneGame::Update(sf::Time deltaTime)
{
	level.Update(deltaTime);
}

void SceneGame::RenderGUI(sf::RenderWindow *window)
{
	level.RenderGUI(window);
}

void SceneGame::RenderSFML(sf::RenderWindow *window)
{
	level.RenderSFML(window);
}