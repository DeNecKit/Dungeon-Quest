#include "SceneMainMenu.h"
#include "GameManager.h"

void OnClickNewGame(const sf::Event&) {}

void OnClickLoadGame(const sf::Event&) {}

void OnClickExit(const sf::Event&)
{
	GameManager::Close();
}

SceneMainMenu::SceneMainMenu()
{
	font_tmp = new sf::Font();
	if (!font_tmp->loadFromFile("data/font.ttf"))
		throw std::exception();

	GuiStyle style = GuiStyle(sf::Color::Black,
		sf::Color::White, sf::Color::White);
	const int w = 500;
	constexpr const int x = 1920 / 2 - w / 2;

	title = new GuiText(sf::Vector2f(x, 100), style, "Dungeon Quest", font_tmp, 24);

	sf::Vector2f size(w, 100);
	btnNewGame = new GuiButton(sf::Vector2f(x, 500), size,
		style, L"Новая игра", font_tmp, 16, OnClickNewGame);
	btnLoadGame = new GuiButton(sf::Vector2f(x, 650), size,
		style, L"Загрузить игру", font_tmp, 16, OnClickLoadGame);
	btnExit = new GuiButton(sf::Vector2f(x, 800), size,
		style, L"Выйти", font_tmp, 16, OnClickExit);
}

SceneMainMenu::~SceneMainMenu()
{
	delete btnNewGame;
	delete btnLoadGame;
	delete btnExit;
	delete font_tmp;
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