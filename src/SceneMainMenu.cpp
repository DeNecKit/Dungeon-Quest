#include "SceneMainMenu.h"
#include "GameManager.h"
#include "ResourceManager.h"

SceneMainMenu::SceneMainMenu()
{
	GuiStyle style = GuiStyle(sf::Color::Black,
		sf::Color::White, sf::Color::White);
	const float w = 500.f * (int)GameManager::WindowWidth() / 1920;
	const float x = (int)GameManager::WindowWidth() / 2.f - w / 2;
	sf::Vector2f size(w, 100);

	title = new GuiText(sf::Vector2f(x, 100), size, style,
		"Dungeon Quest", ResourceManager::GetMainFont(), 48);

	btnNewGame = new GuiButton(sf::Vector2f(x, 500), size,
		style, L"Новая игра", ResourceManager::GetMainFont(), 24,
		[](const sf::Event&) {});
	btnLoadGame = new GuiButton(sf::Vector2f(x, 650), size,
		style, L"Загрузить игру", ResourceManager::GetMainFont(), 24,
		[](const sf::Event&) {});
	btnExit = new GuiButton(sf::Vector2f(x, 800), size,
		style, L"Выйти", ResourceManager::GetMainFont(), 24,
		[](const sf::Event&) {
			GameManager::Close();
		});
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

void SceneMainMenu::Update(float deltaTime)
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