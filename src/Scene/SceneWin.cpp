#include "SceneWin.h"
#include "SceneMainMenu.h"
#include "../SceneManager.h"

SceneWin::SceneWin()
{
	const float ww = 1920.f, hww = ww/2, wh = 1080.f, hwh = wh/2,
		w = 500.f, h = 100.f, d = 50.f, x = hww-w/2, y1 = hwh-(h*3+d*2)/2;
	text1 = new GuiText({x, y1, w, h}, L"Вы освободили принцессу!", 48);
	text2 = new GuiText({x, y1+d+h, w, h}, L"Игра пройдена!", 48);
	back = new GuiButton({x, y1+d*3+h*2, w, h}, L"Вернуться в главное меню", 24,
		[](const sf::Event&) { SceneManager::ChangeScene<SceneMainMenu>(); });
}

SceneWin::~SceneWin()
{
	delete text1;
	delete text2;
	delete back;
}

void SceneWin::ProcessEvent(const sf::Event &event)
{
	back->ProcessEvent(event);
}

void SceneWin::Update(sf::Time deltaTime)
{
	back->Update(deltaTime);
}

void SceneWin::RenderGUI(sf::RenderWindow *window)
{
	text1->Render(window);
	text2->Render(window);
	back->Render(window);
}

void SceneWin::RenderSFML(sf::RenderWindow*) {}