#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include "SceneManager.h"
#include "ResourceManager.h"
#include <cstdlib>
#include <format>
#include <ctime>
#include "Gui/GuiText.h"

GuiText *fpsText = nullptr;
float framesCount = 0;
sf::Time passedTime = sf::Time::Zero;
bool showFps = true;

void GameManager::Init()
{
	std::srand((unsigned int)std::time(nullptr));
	window = new sf::RenderWindow(
		sf::VideoMode::getDesktopMode(),
		"Dungeon Quest", sf::Style::Fullscreen);
	window->setFramerateLimit(60);
	deltaClock.restart();
	fpsText = new GuiText(sf::FloatRect(10.f, 10.f, 50.f, 25.f), "NaN", 18,
		ResourceManager::GetMainFont(), sf::Color::White, sf::Color::Black);
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
	{
		SceneManager::ProccessEvent(event);
		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::F3)
			showFps = !showFps;
	}

	sf::Time dt = deltaClock.restart();
	if (showFps)
	{
		framesCount++;
		passedTime += dt;
		fpsText->SetString(std::format("{:.1f}",
			framesCount / passedTime.asSeconds()));
		if (passedTime > sf::seconds(1.f))
		{
			framesCount = 0;
			passedTime = sf::Time::Zero;
		}
	}
	SceneManager::Update(dt);

	window->clear(backgroundColor);
	SceneManager::RenderSFML(window);
	SceneManager::RenderGUI(window);
	if (showFps) fpsText->Render(window);
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
	delete fpsText;
	delete window;
	SceneManager::Shutdown();
	ResourceManager::Shutdown();
}