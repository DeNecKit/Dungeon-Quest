#include "SceneLoadGame.h"
#include "SceneMainMenu.h"
#include "../SceneManager.h"
#include <filesystem>

SceneLoadGame::SceneLoadGame()
{
	std::vector<std::string> savePaths;
	for (const auto &file : std::filesystem::directory_iterator("data/saves"))
	{
		auto path = file.path().string();
		if (path != "data/saves\\global.json")
			savePaths.push_back(path);
	}

	const float hww = 1920.f/2, hwh = 1080.f/2,
		tw = 500.f, th = 100.f, bw = tw, bh = th,
		d = 50.f, sd = d/2, lw = bw+d*2, lh = bh*5+d*2+sd*4,
		tx = hww-tw/2, ty = hwh-(th+lh+bh+d*2)/2,
		lx = hww-lw/2, ly = ty+th+d,
		bx = hww-bw/2, by = ly+lh+d;
	text = new GuiText({tx, ty, tw, th}, L"Выберите сохранение", 48);
	saves = new GuiList({lx, ly, lw, lh});
	for (int i = 0; i < 5; i++)
		saves->Append(new GuiButton({lx+d, ly+d+(bh+sd)*i, bw, bh},
			L"Сохранение " + std::to_wstring(i+1), 24, [](const sf::Event&) {}));
	back = new GuiButton({bx, by, bw, bh}, L"Вернуться в главное меню", 24,
		[](const sf::Event&) { SceneManager::ChangeScene<SceneMainMenu>(); });
}

SceneLoadGame::~SceneLoadGame()
{
	delete text;
	delete saves;
	delete back;
}

void SceneLoadGame::ProcessEvent(const sf::Event &event)
{
	saves->ProcessEvent(event);
	back->ProcessEvent(event);
}

void SceneLoadGame::Update(sf::Time deltaTime)
{
	saves->Update(deltaTime);
	back->Update(deltaTime);
}

void SceneLoadGame::RenderGUI(sf::RenderWindow *window)
{
	text->Render(window);
	saves->Render(window);
	back->Render(window);
}

void SceneLoadGame::RenderSFML(sf::RenderWindow*) {}