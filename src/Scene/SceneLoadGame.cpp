#include "SceneLoadGame.h"
#include "SceneMainMenu.h"
#include "SceneGame.h"
#include "../SceneManager.h"
#include "../Level.h"
#include <filesystem>
#include <fstream>
#include <cmath>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

const unsigned int savesPerPage = 5;
const float hww = 1920.f/2, hwh = 1080.f/2,
tw = 500.f, th = 100.f, bw = tw, bh = th,
d = 50.f, sd = d/2, lw = bw+d*2, lh = bh*5+d*2+sd*4,
ptw = 100.f, pth = 50.f, pbw = pth, pbh = pth,
tx = hww-tw/2, ty = hwh-(th+lh+pth+bh+sd*3)/2,
lx = hww-lw/2, ly = ty+th+sd,
ptx = hww-ptw/2, pty = ly+lh+sd,
pbx1 = ptx-d-pbw, pbx2 = ptx+ptw+d, pby = pty,
bx = hww-bw/2, by = pty+pth+sd;

SceneLoadGame::SceneLoadGame()
{
	instance = this;

	for (const auto &file : std::filesystem::directory_iterator("data/saves"))
	{
		auto path = file.path().string();
		if (path != "data/saves\\global.json")
			savePaths.push_back(path);
	}
	for (const auto &path : savePaths)
	{
		std::ifstream saveFile(path);
		if (!saveFile.is_open()) throw new std::exception();
		json data = json::parse(saveFile);
		saveFile.close();
		saveNames.push_back(L"Уровень " + std::to_wstring((int)data["level"]["num"])
			+ L"\nУровень игрока: " + std::to_wstring((int)data["player"]["lvl"]));
	}
	pagesNum = std::max((int)std::ceilf((float)saveNames.size() / savesPerPage), 1);
	curPage = 1;

	text = new GuiText({tx, ty, tw, th}, L"Выберите сохранение", 48);
	pageNum = new GuiText({ptx, pty, ptw, pth}, "", 24);
	pagePrev = new GuiButton({pbx1, pby, pbw, pbh}, "<-", 24,
		[](Gui *self) { SceneLoadGame::PrevPage(); });
	pageNext = new GuiButton({pbx2, pby, pbw, pbh}, "->", 24,
		[](Gui *self) { SceneLoadGame::NextPage(); });
	SetPage(curPage);
	back = new GuiButton({bx, by, bw, bh}, L"Вернуться в главное меню", 24,
		[](Gui *self) { SceneManager::ChangeScene<SceneMainMenu>(); });
}

SceneLoadGame::~SceneLoadGame()
{
	delete text;
	delete saves;
	delete pageNum;
	delete pagePrev;
	delete pageNext;
	delete back;
	instance = nullptr;
}

void SceneLoadGame::ProcessEvent(const sf::Event &event)
{
	saves->ProcessEvent(event);
	pagePrev->ProcessEvent(event);
	pageNext->ProcessEvent(event);
	back->ProcessEvent(event);
}

void SceneLoadGame::Update(sf::Time deltaTime)
{
	saves->Update(deltaTime);
	pagePrev->Update(deltaTime);
	pageNext->Update(deltaTime);
	back->Update(deltaTime);
}

void SceneLoadGame::RenderGUI(sf::RenderWindow *window)
{
	text->Render(window);
	saves->Render(window);
	pagePrev->Render(window);
	pageNext->Render(window);
	pageNum->Render(window);
	back->Render(window);
}

void SceneLoadGame::RenderSFML(sf::RenderWindow*) {}

std::vector<std::string> SceneLoadGame::GetSavePaths()
{
	return instance->savePaths;
}

unsigned int SceneLoadGame::GetBtnNum(Gui *btn)
{
	return instance->btnNum[btn];
}

void SceneLoadGame::PrevPage()
{
	instance->SetPage(--instance->curPage);
}

void SceneLoadGame::NextPage()
{
	instance->SetPage(++instance->curPage);
}

void SceneLoadGame::SetPage(unsigned int page)
{
	if (saves != nullptr) delete saves;
	btnNum.clear();
	saves = new GuiList({lx, ly, lw, lh});
	int j = 0;
	for (int i = (page-1)*savesPerPage; j < savesPerPage; i++, j++)
		if (i < saveNames.size())
		{
			GuiButton *btn = new GuiButton({lx+d, ly+d+(bh+sd)*j, bw, bh},
				saveNames[i], 24, [](Gui* self) {
					Level::Load(SceneLoadGame::GetSavePaths()[SceneLoadGame::GetBtnNum(self)]);
					SceneManager::ChangeScene<SceneGame>();
				});
			btnNum[btn->GetClickable()] = j;
			saves->Append(btn);
		}
		else
		{
			auto btn = new GuiButton({lx+d, ly+d+(bh+sd)*j, bw, bh},
				L"-Пусто-", 24, [](Gui *self) {});
			btn->SetEnabled(false);
			saves->Append(btn);
		}

	pageNum->SetString(std::to_wstring(page) + L" стр.");
	pagePrev->SetEnabled(page > 1);
	pageNext->SetEnabled(page < pagesNum);
}