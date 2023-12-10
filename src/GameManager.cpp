#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include "SceneManager.h"
#include "ResourceManager.h"
#include <cstdlib>
#include <ctime>

void GameManager::Init()
{
	std::srand((unsigned int)std::time(nullptr));
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

float GameManager::ResCoefX()
{
	return (int)WindowWidth() / 1920.f;
}

float GameManager::ResCoefY()
{
	return (int)WindowHeight() / 1080.f;
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

	sf::Time dt = deltaClock.restart();
	SceneManager::Update(dt);

	window->clear(backgroundColor);
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
	ResourceManager::Shutdown();
}