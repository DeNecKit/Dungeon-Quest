#include "SceneManager.h"
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "SceneMainMenu.h"

void SceneManager::Init()
{
	currentScene = new SceneMainMenu();
}

template<typename T>
void SceneManager::ChangeScene()
{
	delete currentScene;
	currentScene = new T();
}

void SceneManager::ProccessEvent(const sf::Event &event)
{
	if (event.type == sf::Event::Closed)
	{
		GameManager::Close();
		return;
	}
	if (currentScene != nullptr)
		currentScene->ProcessEvent(event);
}

void SceneManager::Update(sf::Time deltaTime)
{
	if (currentScene != nullptr)
		currentScene->Update(deltaTime);
}

void SceneManager::RenderGUI(sf::RenderWindow* window)
{
	if (currentScene != nullptr)
		currentScene->RenderGUI(window);
}

void SceneManager::RenderSFML(sf::RenderWindow *window)
{
	if (currentScene != nullptr)
		currentScene->RenderSFML(window);
}

void SceneManager::Shutdown()
{
	if (currentScene != nullptr)
		delete currentScene;
}