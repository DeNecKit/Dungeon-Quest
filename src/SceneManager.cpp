#include "SceneManager.h"
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Scene/SceneMainMenu.h"
#include "Scene/SceneGame.h"
#include "Scene/SceneBattle.h"
#include "Level.h"

void SceneManager::Init()
{
	currentScene = new SceneMainMenu();
	isSceneChanged = false;
}

template<typename T>
void SceneManager::ChangeScene()
{
	if (dynamic_cast<SceneMainMenu*>(currentScene) &&
		typeid(T) == typeid(SceneGame))
		Level::Change(Level::Level1());
	tmpScene = new T();
	isSceneChanged = true;
}

template void SceneManager::ChangeScene<SceneMainMenu>();
template void SceneManager::ChangeScene<SceneGame>();
template void SceneManager::ChangeScene<SceneBattle>();

void SceneManager::ProccessEvent(const sf::Event &event)
{
	if (isSceneChanged)
	{
		if (dynamic_cast<SceneGame*>(currentScene) &&
			dynamic_cast<SceneMainMenu*>(tmpScene))
			Level::Reset();
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