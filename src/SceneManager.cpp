#include "SceneManager.hpp"
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"

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

void SceneManager::RenderGUI()
{
	if (m_currentScene != nullptr)
		m_currentScene->RenderGUI();
}

void SceneManager::RenderSFML()
{
	if (m_currentScene != nullptr)
		m_currentScene->RenderSFML();
}

void SceneManager::Shutdown()
{
	if (m_currentScene != nullptr)
		delete m_currentScene;
}