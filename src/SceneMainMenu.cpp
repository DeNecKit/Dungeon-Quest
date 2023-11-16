#include "SceneMainMenu.h"

void OnHover(const sf::Event&) {}

void OnClickNewGame(const sf::Event&) {}
void OnClickLoadGame(const sf::Event&) {}
void OnClickExit(const sf::Event&) {}

SceneMainMenu::SceneMainMenu()
{
	GuiStyle style = GuiStyle(sf::Color::Black,
		sf::Color::White, sf::Color());
	style.SetCoords(sf::Vector2f(100, 100), sf::Vector2f(200, 100));
	btnNewGame = new GuiButton(style, "Новая игра", OnClickNewGame, OnHover);
	style.SetCoords(sf::Vector2f(100, 300), sf::Vector2f(200, 100));
	btnLoadGame = new GuiButton(style, "Загрузить игру", OnClickLoadGame, OnHover);
	style.SetCoords(sf::Vector2f(100, 500), sf::Vector2f(200, 100));
	btnExit = new GuiButton(style, "Выйти", OnClickExit, OnHover);
}

SceneMainMenu::~SceneMainMenu()
{
	if (btnNewGame != nullptr)
		delete btnNewGame;
	if (btnLoadGame != nullptr)
		delete btnLoadGame;
	if (btnExit != nullptr)
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
	btnNewGame->Update();
	btnLoadGame->Update();
	btnExit->Update();
}

void SceneMainMenu::RenderGUI()
{
	btnNewGame->Render();
	btnLoadGame->Render();
	btnExit->Render();
}

void SceneMainMenu::RenderSFML() {}