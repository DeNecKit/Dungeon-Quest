#include "SceneManager.h"
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Scene/SceneMainMenu.h"
#include "Scene/SceneGame.h"
#include "Scene/SceneBattle.h"
#include "Scene/SceneWin.h"
#include "Scene/SceneLoadGame.h"
#include "Level.h"
#include "Item/Item.h"
#include "Item/ItemTemplate.h"

void SceneManager::Init()
{
	currentScene = new SceneMainMenu();
	isSceneChanged = false;
	ItemTemplate::Init();
	Item::Init();
}

template<typename T>
void SceneManager::ChangeScene()
{
	if (dynamic_cast<SceneMainMenu*>(currentScene) &&
		typeid(T) == typeid(SceneGame))
		Level::Change(Level::Level1());
		//Level::Change(Level::Level2());
		//Level::Change(Level::Level3());
	tmpScene = new T();
	isSceneChanged = true;
}

template void SceneManager::ChangeScene<SceneMainMenu>();
template void SceneManager::ChangeScene<SceneGame>();
template void SceneManager::ChangeScene<SceneBattle>();
template void SceneManager::ChangeScene<SceneWin>();
template void SceneManager::ChangeScene<SceneLoadGame>();

Scene *SceneManager::GetCurrentScene()
{
	return currentScene;
}

void SceneManager::ProccessEvent(const sf::Event &event)
{
	if (isSceneChanged)
	{
		delete currentScene;
		if (dynamic_cast<SceneMainMenu*>(tmpScene))
		{
			Level::Reset();
			Item::Clear();
		}
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
	Item::Shutdown();
	ItemTemplate::Shutdown();
}