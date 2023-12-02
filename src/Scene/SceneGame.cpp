#include "SceneGame.h"
#include "../SceneManager.h"
#include "SceneMainMenu.h"
#include "../GameManager.h"
#include "../ResourceManager.h"

SceneGame::SceneGame()
	: level(Level::Level1()), isInterTextVisible(false)
{
	instance = this;
	interText = new GuiText(
		sf::FloatRect(1920.f/2 - 200.f/2, 1080.f/2 + 100.f, 200.f, 100.f),
		L"Нажмите \"E\" для взаимодействия", ResourceManager::GetMainFont(),
		18, sf::Color(255, 255, 255, 200), sf::Color::Black);
}

SceneGame::~SceneGame()
{
	delete level;
	delete interText;
}

void SceneGame::ProcessEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed
		&& event.key.code == sf::Keyboard::Escape)
		SceneManager::ChangeScene<SceneMainMenu>();
	isInterTextVisible = false;
	level->ProcessEvent(event);
}

void SceneGame::Update(sf::Time deltaTime)
{
	level->Update(deltaTime);
	if (isInterTextVisible)
		interText->Update(deltaTime);
}

void SceneGame::RenderGUI(sf::RenderWindow *window)
{
	level->RenderGUI(window);
	if (isInterTextVisible)
		interText->Render(window);
}

void SceneGame::RenderSFML(sf::RenderWindow *window)
{
	level->RenderSFML(window);
}

void SceneGame::InteractionNotify()
{
	instance->isInterTextVisible = true;
}