#include "SceneMainMenu.h"
#include "../GameManager.h"
#include "../ResourceManager.h"
#include "SceneGame.h"

SceneMainMenu::SceneMainMenu()
{
	const float w = 500.f, x = 1920.f / 2 - w / 2;

	sf::Color textColor = sf::Color::White,
		shadowColor = sf::Color(128, 128, 128),
		fillColor = sf::Color::Black,
		outlineColor = sf::Color::White;

	title = new GuiText(sf::FloatRect(x, 100, w, 100),
		"Dungeon Quest", ResourceManager::GetMainFont(), 48,
		textColor, shadowColor);

	btnNewGame = new GuiButton(sf::FloatRect(x, 500, w, 100),
		L"Новая игра", ResourceManager::GetMainFont(), 24,
		[](const sf::Event&) { SceneManager::ChangeScene<SceneGame>(); },
		fillColor, textColor, outlineColor, shadowColor);

	btnLoadGame = new GuiButton(sf::FloatRect(x, 650, w, 100),
		L"Загрузить игру", ResourceManager::GetMainFont(), 24,
		[](const sf::Event&) {},
		fillColor, textColor, outlineColor, shadowColor);

	btnExit = new GuiButton(sf::FloatRect(x, 800, w, 100),
		L"Выйти", ResourceManager::GetMainFont(), 24,
		[](const sf::Event&) { GameManager::Close(); },
		fillColor, textColor, outlineColor, shadowColor);
}

SceneMainMenu::~SceneMainMenu()
{
	delete title;
	delete btnNewGame;
	delete btnLoadGame;
	delete btnExit;
}

void SceneMainMenu::ProcessEvent(const sf::Event &event)
{
	btnNewGame->ProcessEvent(event);
	btnLoadGame->ProcessEvent(event);
	btnExit->ProcessEvent(event);
}

void SceneMainMenu::Update(sf::Time deltaTime)
{
	btnNewGame->Update(deltaTime);
	btnLoadGame->Update(deltaTime);
	btnExit->Update(deltaTime);
}

void SceneMainMenu::RenderGUI(sf::RenderWindow *window)
{
	title->Render(window);
	btnNewGame->Render(window);
	btnLoadGame->Render(window);
	btnExit->Render(window);
}

void SceneMainMenu::RenderSFML(sf::RenderWindow *window) {}