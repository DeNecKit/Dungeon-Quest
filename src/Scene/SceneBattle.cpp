#include "SceneBattle.h"
#include "../SceneManager.h"
#include "SceneGame.h"

SceneBattle::SceneBattle()
{
}

void SceneBattle::ProcessEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed &&
		event.key.code == sf::Keyboard::Escape)
		SceneManager::ChangeScene<SceneGame>();
}

void SceneBattle::Update(sf::Time deltaTime)
{
}

void SceneBattle::RenderGUI(sf::RenderWindow*)
{
}

void SceneBattle::RenderSFML(sf::RenderWindow*)
{
}