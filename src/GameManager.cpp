#include "GameManager.h"
#include <SFML/Graphics.hpp>
#include "SceneManager.h"
#include "ResourceManager.h"
#include <cstdlib>
#include <format>
#include <ctime>
#include "Gui/GuiText.h"
#include "Gui/GuiRect.h"

GuiText *fpsText = nullptr;
GuiRect *fpsBackground = nullptr;
float fps = 0.f;
bool showFps = true;

void GameManager::Init()
{
	std::srand((unsigned int)std::time(nullptr));
	window = new sf::RenderWindow(
		sf::VideoMode::getDesktopMode(),
		"Dungeon Quest", sf::Style::Fullscreen);
	window->setFramerateLimit(60);
	deltaClock.restart();
	fpsText = new GuiText(sf::FloatRect(16.f, 11.f, 50.f, 25.f), "NaN", 18, false,
		ResourceManager::GetMainFont(), sf::Color::White, sf::Color::Black);
	fpsBackground = new GuiRect(sf::FloatRect(9.f, 10.f, 136.f, 32.f),
		sf::Color(0, 0, 0, 100));
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
		const float smoothing = 0.92f;
		fps = fps*smoothing + 1/dt.asSeconds()*(1-smoothing);
		fpsText->SetString("FPS: " + std::format("{:.1f}", fps));
	}
	SceneManager::Update(dt);

	window->clear(backgroundColor);
	SceneManager::RenderSFML(window);
	SceneManager::RenderGUI(window);
	if (showFps)
	{
		fpsBackground->Render(window);
		fpsText->Render(window);
	}
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

bool GameManager::IsMouseOver(sf::FloatRect rect)
{
	sf::Vector2i mPos = sf::Mouse::getPosition(*window);
	int mx = mPos.x, my = mPos.y,
		x = (int)rect.left, y = (int)rect.top,
		w = (int)rect.width, h = (int)rect.height;
	return mx >= x && mx <= x + w && my >= y && my <= y + h;;
}