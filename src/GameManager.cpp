#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include "SceneManager.h"

void GameManager::Init()
{
	window = new sf::RenderWindow(
		sf::VideoMode::getDesktopMode(),
		"Dungeon Quest", sf::Style::Fullscreen);
	window->setFramerateLimit(60);
	deltaClock.restart();
	SceneManager::Init();
}

sf::RenderWindow* GameManager::GetWindow()
{
	return window;
}

unsigned int GameManager::WindowWidth()
{
	return window->getSize().x;
}

unsigned int GameManager::WindowHeight()
{
	return window->getSize().y;
}

bool GameManager::IsRunning()
{
	return !isWindowClosed;
}

void GameManager::Update()
{
	sf::Event event;
	while (window->pollEvent(event))
		SceneManager::ProccessEvent(event);

	float dt = deltaClock.restart().asSeconds();
	SceneManager::Update(dt);

	window->clear(sf::Color(36, 36, 36));
	SceneManager::RenderSFML(window);
	SceneManager::RenderGUI(window);
	window->display();
}

void GameManager::Close()
{
	if (isWindowClosed) return;
	window->close();
	isWindowClosed = true;
}

void GameManager::Shutdown()
{
	delete window;
	SceneManager::Shutdown();
}