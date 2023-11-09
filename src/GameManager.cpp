#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include "SceneManager.h"

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

unsigned int GameManager::WindowWidth()
{
	return m_window->getSize().x;
}

unsigned int GameManager::WindowHeight()
{
	return m_window->getSize().y;
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

	float dt = m_deltaClock.restart().asSeconds();
	SceneManager::Update(dt);

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