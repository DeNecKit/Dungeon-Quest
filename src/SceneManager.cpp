#include "SceneManager.h"
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "SceneMainMenu.h"

void SceneManager::Init()
{
	currentScene = new SceneMainMenu();
	isSceneChanged = false;
}

void SceneManager::ProccessEvent(const sf::Event &event)
{
	if (isSceneChanged)
	{
		delete currentScene;
		currentScene = tmpScene;
		tmpScene = nullptr;
		isSceneChanged = false;
	}
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