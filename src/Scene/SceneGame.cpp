#include "SceneGame.h"
#include "../SceneManager.h"
#include "SceneMainMenu.h"
#include "../GameManager.h"
#include "../ResourceManager.h"
#include "../Gui/GuiButton.h"

SceneGame::SceneGame()
	: level(Level::Level1()),
	isInterTextVisible(false), isPaused(false)
{
	instance = this;
	sf::Color textColor = sf::Color::White,
		shadowColor = sf::Color(128, 128, 128),
		fillColor = sf::Color::Black,
		outlineColor = sf::Color::White;

	interText = new GuiText(
		sf::FloatRect(1920.f/2 - 200.f/2, 1080.f/2 + 100.f, 200.f, 100.f),
		L"Нажмите \"E\" для взаимодействия", ResourceManager::GetMainFont(),
		18, sf::Color(255, 255, 255, 200), sf::Color::Black);

	const float hww = 1920.f / 2, hwh = 1080.f / 2,
		w = 500.f, h = 100.f, d = 50.f,
		lw = w + d*2, lh = h*3 + d*4;

	pauseMenu = new GuiList(
		sf::FloatRect(hww - lw/2, hwh - lh/2, lw, lh),
		fillColor, outlineColor);

	pauseMenu->Append(new GuiButton(
		sf::FloatRect(hww - w/2, hwh - lh/2 + d, w, h),
		L"Вернуться в игру", ResourceManager::GetMainFont(), 24,
		[](const sf::Event&) { SetPause(false); },
		fillColor, textColor, outlineColor, shadowColor));

	pauseMenu->Append(new GuiButton(
		sf::FloatRect(hww - w / 2, hwh - lh / 2 + d*2 + h, w, h),
		L"Сохранить игру", ResourceManager::GetMainFont(), 24,
		[](const sf::Event&) {},
		fillColor, textColor, outlineColor, shadowColor));

	pauseMenu->Append(new GuiButton(
		sf::FloatRect(hww - w / 2, hwh - lh / 2 + d*3 + h*2, w, h),
		L"Выйти в главное меню", ResourceManager::GetMainFont(), 24,
		[](const sf::Event&) { SceneManager::ChangeScene<SceneMainMenu>(); },
		fillColor, textColor, outlineColor, shadowColor));
}

SceneGame::~SceneGame()
{
	delete level;
	delete interText;
	delete pauseMenu;
}

void SceneGame::ProcessEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed
		&& event.key.code == sf::Keyboard::Escape)
		isPaused = !isPaused;
	isInterTextVisible = false;
	if (!isPaused)
		level->ProcessEvent(event);
	else pauseMenu->ProcessEvent(event);
}

void SceneGame::Update(sf::Time deltaTime)
{
	if (!isPaused)
	{
		level->Update(deltaTime);
		if (isInterTextVisible)
			interText->Update(deltaTime);
	} else pauseMenu->Update(deltaTime);
}

void SceneGame::RenderGUI(sf::RenderWindow *window)
{
	if (isInterTextVisible)
		interText->Render(window);
	if (isPaused) pauseMenu->Render(window);
}

void SceneGame::RenderSFML(sf::RenderWindow *window)
{
	level->RenderSFML(window);
}

void SceneGame::InteractionNotify()
{
	instance->isInterTextVisible = true;
}

void SceneGame::SetPause(bool pause)
{
	instance->isPaused = pause;
}