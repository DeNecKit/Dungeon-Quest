#include "SceneManager.h"
#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "SceneMainMenu.h"

void SceneManager::Init()
{
	m_currentScene = new SceneMainMenu();
}

void SceneManager::ProccessEvent(const sf::Event &event)
{
	if (event.type == sf::Event::Closed)
	{
		GameManager::Close();
		return;
	}
	if (m_currentScene != nullptr)
		m_currentScene->ProcessEvent(event);
}

void SceneManager::Update(float deltaTime)
{
	if (m_currentScene != nullptr)
		m_currentScene->Update(deltaTime);
}

void SceneManager::RenderGUI(sf::RenderWindow* window)
{
	if (m_currentScene != nullptr)
		m_currentScene->RenderGUI(window);
}

void SceneManager::RenderSFML(sf::RenderWindow *window)
{
	if (m_currentScene != nullptr)
		m_currentScene->RenderSFML(window);
}

void SceneManager::Shutdown()
{
	if (m_currentScene != nullptr)
		delete m_currentScene;
}