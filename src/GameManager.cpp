#include "GameManager.hpp"
#include <SFML/Graphics.hpp>
#include "SceneManager.hpp"

void GameManager::Init()
{
	m_window = new sf::RenderWindow(
		sf::VideoMode::getDesktopMode(),
		"Dungeon Quest", sf::Style::Fullscreen);
	m_window->setFramerateLimit(60);
	m_deltaClock.restart();
	SceneManager::Init();
}

sf::RenderWindow* GameManager::GetWindow()
{
	return m_window;
}

bool GameManager::IsRunning()
{
	return !m_isWindowClosed;
}

void GameManager::Update()
{
	sf::Event event;
	while (m_window->pollEvent(event))
		SceneManager::ProccessEvent(event);
	sf::Time dt = m_deltaClock.restart();

	m_window->clear(sf::Color(36, 36, 36));
	SceneManager::RenderSFML();
	SceneManager::RenderGUI();
	m_window->display();
}

void GameManager::Close()
{
	if (m_isWindowClosed) return;
	m_window->close();
	m_isWindowClosed = true;
}

void GameManager::Shutdown()
{
	delete m_window;
	SceneManager::Shutdown();
}