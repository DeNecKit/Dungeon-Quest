#include "SceneMainMenu.h"
#include "../GameManager.h"
#include "../ResourceManager.h"
#include "SceneGame.h"
#include "SceneLoadGame.h"
#include "../Level.h"

SceneMainMenu::SceneMainMenu()
{
	const float w = 500.f, x = 1920.f / 2 - w / 2;

	sf::Color textColor = sf::Color::White,
		shadowColor = sf::Color(128, 128, 128),
		fillColor = sf::Color::Black,
		outlineColor = sf::Color::White;

	title = new GuiText(sf::FloatRect(x, 100.f, w, 200.f), "Dungeon Quest", 96);

	btnNewGame = new GuiButton(sf::FloatRect(x, 500.f, w, 100.f),
		L"Новая игра", 24, [](Gui *self)
			{ SceneManager::ChangeScene<SceneGame>(); });

	btnLoadGame = new GuiButton(sf::FloatRect(x, 650.f, w, 100.f),
		L"Загрузить игру", 24, [](Gui *self)
			{ SceneManager::ChangeScene<SceneLoadGame>(); });

	btnExit = new GuiButton(sf::FloatRect(x, 800.f, w, 100.f),
		L"Выйти", 24, [](Gui *self) { GameManager::Close(); });
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