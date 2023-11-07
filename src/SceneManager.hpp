#pragma once

#include <SFML/Graphics.hpp>
#include "GameManager.hpp"
#include "Scene.hpp"

class SceneManager
{
public:
	static void Init()
	{
		m_currentScene = new SceneMainMenu();
	}

	static void ProccessEvent(const sf::Event &event)
	{
		if (event.type == sf::Event::Closed)
		{
			GameManager::CloseWindow();
			return;
		}
		if (m_currentScene != nullptr)
			m_currentScene->ProcessEvent(event);
	}

	static void RenderGUI()
	{
		if (m_currentScene != nullptr)
			m_currentScene->RenderGUI();
	}

	static void RenderSFML()
	{
		if (m_currentScene != nullptr)
			m_currentScene->RenderSFML();
	}

	static void Shutdown()
	{
		if (m_currentScene != nullptr)
			delete m_currentScene;
	}

private:
	static inline Scene *m_currentScene;
};