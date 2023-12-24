#include "SceneGame.h"
#include "../SceneManager.h"
#include "SceneMainMenu.h"
#include "../GameManager.h"
#include "../ResourceManager.h"
#include "../Gui/GuiButton.h"
#include "../Gui/GuiItemSlot.h"
#include "../Gui/GuiProgressBar.h"
#include "../Item/ItemTemplate.h"
#include "../Level.h"

SceneGame::SceneGame()
	: isInterTextVisible(false), isPaused(false), isInvMenu(false), openedChest(nullptr)
{
	instance = this;
	const float hww = 1920.f/2, hwh = 1080.f/2;
	interText = new GuiText(
		sf::FloatRect(hww - 200.f/2, hwh * 1.5f, 200.f, 100.f),
		L"Нажмите \"F\" для взаимодействия", 18,
		true, ResourceManager::GetMainFont(),
		sf::Color(255, 255, 255, 200), sf::Color::Black);

	const float w = 500.f, h = 100.f, d = 50.f,
		lw = w + d*2, lh = h*4 + d*5,
		lx = hww - lw/2, ly = hwh - lh/2;
	pauseMenu = new GuiList(sf::FloatRect(lx, ly, lw, lh));
	pauseMenu->Append(new GuiText(sf::FloatRect(lx + d, ly + d, w, h), L"Пауза", 48));
	pauseMenu->Append(new GuiButton(sf::FloatRect(lx + d, ly + d*2 + h, w, h),
		L"Вернуться в игру", 24, [](Gui *self) { SetPause(false); }));
	pauseMenu->Append(new GuiButton(sf::FloatRect(lx + d, ly + d*3 + h*2, w, h),
		L"Сохранить игру", 24, [](Gui *self) { Level::Save(); }));
	pauseMenu->Append(new GuiButton(sf::FloatRect(lx + d, ly + d*4 + h*3, w, h),
		L"Выйти в главное меню", 24, [](Gui *self)
			{ SceneManager::ChangeScene<SceneMainMenu>(); }));

	const float n = 5, m = 3, s = 100.f,
		iw = s*n + d*(n+1), ih = s*m + d*(m+1) + s,
		ew = iw, eh = s*2 + d*2,
		cw = iw, ch = ih,
		ix = d, iy = hwh - (ih + d + eh)/2,
		ex = ix, ey = iy + ih + d,
		cx = hww*2 - cw - d, cy = iy,
		x0 = ix + d, y0 = iy + s + d,
		x1 = ex + d, y1 = ey + s + d,
		x2 = cx + d, y2 = cy + s + d;
	inventoryGui = GuiList::CreatePlayerInventory();
	equipmentGui = new GuiList(sf::FloatRect(ex, ey, ew, eh),
		true, Gui::ButtonFillColor, Gui::ButtonOutlineColor);
	equipmentGui->Append(new GuiText(
		sf::FloatRect(ex, ey, ew, s), L"Экипировка", 48));
	for (int x = 0; x < n; x++)
		equipmentGui->Append(new GuiItemSlot(
			sf::FloatRect(x1 + x*(s+d), y1, s, s),
			nullptr, 15+x, (SlotType)(x + 1), Player::GetItem(15+x)));
	chestGui = new GuiList(sf::FloatRect(cx, cy, cw, ch),
		true, Gui::ButtonFillColor, Gui::ButtonOutlineColor);
	chestGui->Append(new GuiText(
		sf::FloatRect(cx, cy, cw, s), L"Сундук", 48));
	for (int y = 0; y < m; y++)
		for (int x = 0; x < n; x++)
			chestGui->Append(new GuiItemSlot(
				sf::FloatRect(x2 + x*(s+d), y2 + y*(s+d), s, s), nullptr, y*5+x));

	const float sw = cw*0.6f, sh = eh, sx = cx+cw/2-sw/2, sy = ey,
		sth1 = sh*0.25f, sth2 = sh - sth1,
		stx1 = sx, stx2 = sx+34.f, sty1 = sy-5.f, sty2 = sy+sth1+75.f,
		spbw = sw*0.75f, spbh = sth1/3, spbx = sx+sw/2-spbw/2, spby = sty1+75.f;
	statusGui = new GuiList(sf::FloatRect(sx, sy, sw, sh),
		false, Gui::ButtonFillColor, Gui::ButtonOutlineColor);
	statusGui->Append(new GuiText(
		sf::FloatRect(stx1, sty1, sw, sth1), Player::GetLevelString(), 24));
	statusGui->Append(new GuiProgressBar(sf::FloatRect(spbx, spby, spbw, spbh),
		sf::Color(8, 144, 0), Player::GetExp(), Player::GetReqExp()));
	statusGui->Append(new GuiProgressBar(sf::FloatRect(spbx, spby+spbh+15, spbw, spbh),
		Gui::HealthBarFillColor, (unsigned int&)Player::Get()->GetHP(), Player::GetMaxHP()));
	statusGui->Append(new GuiText(
		sf::FloatRect(stx2, sty2, sw, sth2), Player::GetStatsString(), 20, false));
}

SceneGame::~SceneGame()
{
	delete interText;
	delete pauseMenu;
	delete inventoryGui;
	delete equipmentGui;
	delete chestGui;
	delete statusGui;
}

void SceneGame::ProcessEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape)
			if (!isInvMenu) isPaused = !isPaused;
			else
			{
				isInvMenu = false;
				openedChest = nullptr;
			}
		else if (!isPaused && event.key.code == sf::Keyboard::E)
		{
			isInvMenu = !isInvMenu;
			if (!isInvMenu) openedChest = nullptr;
		}
	isInterTextVisible = false;
	if (!isPaused && !isInvMenu)
		Level::Get()->ProcessEvent(event);
	if (isPaused) pauseMenu->ProcessEvent(event);
	if (isInvMenu)
	{
		inventoryGui->ProcessEvent(event);
		equipmentGui->ProcessEvent(event);
		if (openedChest != nullptr) chestGui->ProcessEvent(event);
	}
}

void SceneGame::Update(sf::Time deltaTime)
{
	if (!isPaused && !isInvMenu)
	{
		Level::Get()->Update(deltaTime);
		if (isInterTextVisible)
			interText->Update(deltaTime);
	} else if (isInvMenu)
	{
		inventoryGui->Update(deltaTime);
		equipmentGui->Update(deltaTime);
		statusGui->Update(deltaTime);
		if (openedChest != nullptr) chestGui->Update(deltaTime);
	} else pauseMenu->Update(deltaTime);
}

void SceneGame::RenderGUI(sf::RenderWindow *window)
{
	if (isInterTextVisible)
		interText->Render(window);
	if (isPaused) pauseMenu->Render(window);
	if (isInvMenu)
	{
		inventoryGui->Render(window);
		equipmentGui->Render(window);
		statusGui->Render(window);
		if (openedChest != nullptr) chestGui->Render(window);
	}
	if (renderOnTop.size() > 0)
	{
		for (std::variant<sf::Drawable*, Gui*> obj : renderOnTop)
			if (std::holds_alternative<sf::Drawable*>(obj))
				window->draw(*std::get<sf::Drawable*>(obj));
			else std::get<Gui*>(obj)->Render(window);
		renderOnTop.clear();
	}
}

void SceneGame::RenderSFML(sf::RenderWindow *window)
{
	Level::Get()->RenderSFML(window);
	if (isPaused || isInvMenu)
	{
		sf::RectangleShape r((sf::Vector2f)window->getSize());
		r.setFillColor(sf::Color(0, 0, 0, 127));
		window->draw(r);
	}
}

void SceneGame::InteractionNotify()
{
	instance->isInterTextVisible = true;
}

void SceneGame::SetPause(bool pause)
{
	instance->isPaused = pause;
}

void SceneGame::OpenChest(TileChest *chest)
{
	instance->isInvMenu = true;
	instance->openedChest = chest;
	for (int i = 0; i < 15; i++)
	{
		instance->chestGui->SetParent(i, chest);
		instance->chestGui->SetItem(i, chest->GetItem(i));
	}
}

void SceneGame::RefreshPlayerInventory()
{
	for (int i = 0; i < 15; i++)
		instance->inventoryGui->SetItem(i, Player::GetItem(i));
}

void SceneGame::RenderOnTop(std::variant<sf::Drawable*, Gui*> obj)
{
	instance->renderOnTop.push_back(obj);
}

std::vector<Gui*> SceneGame::GetInventoryGui()
{
	std::vector<Gui*> inv = instance->inventoryGui->GetChildren(),
		eq = instance->equipmentGui->GetChildren(),
		ch = instance->chestGui->GetChildren();
	inv.insert(inv.end(), eq.begin(), eq.end());
	inv.insert(inv.end(), ch.begin(), ch.end());
	return inv;
}

void SceneGame::UpdateStatsText()
{
	Player::UpdateStatsString();
	dynamic_cast<GuiText*>(instance->statusGui->GetChildren()[3])
		->SetString(Player::GetStatsString());
}