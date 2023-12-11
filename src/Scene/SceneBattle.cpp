#include "SceneBattle.h"
#include "../SceneManager.h"
#include "SceneGame.h"
#include "../Battle.h"

SceneBattle::SceneBattle()
{
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
}

void SceneBattle::RenderGUI(sf::RenderWindow*)
{
	
}

void SceneBattle::RenderSFML(sf::RenderWindow *window)
{
	Battle::Get()->Render(window);
}