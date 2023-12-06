#include "SceneGame.h"
#include "../SceneManager.h"
#include "SceneMainMenu.h"
#include "../GameManager.h"
#include "../ResourceManager.h"
#include "../Gui/GuiButton.h"
#include "../Gui/GuiItemSlot.h"
#include "../Item/Item.h"

SceneGame::SceneGame()
	: level(Level::Level1()),
	isInterTextVisible(false), isPaused(false), isInvMenu(false)
{
	instance = this;
	Item::Init();
	sf::Color textColor = sf::Color::White,
		shadowColor = sf::Color(128, 128, 128),
		fillColor = sf::Color::Black,
		outlineColor = sf::Color::White;
	const float hww = 1920.f/2, hwh = 1080.f/2;
	interText = new GuiText(
		sf::FloatRect(hww - 200.f/2, hwh + 100.f, 200.f, 100.f),
		L"������� \"F\" ��� ��������������", ResourceManager::GetMainFont(),
		18, sf::Color(255, 255, 255, 200), sf::Color::Black);

	const float w = 500.f, h = 100.f, d = 50.f,
		lw = w + d*2, lh = h*4 + d*5,
		lx = hww - lw/2, ly = hwh - lh/2;
	pauseMenu = new GuiList(sf::FloatRect(lx, ly, lw, lh), fillColor, outlineColor);
	pauseMenu->Append(new GuiText(sf::FloatRect(lx + d, ly + d, w, h), L"�����",
		ResourceManager::GetMainFont(), 48, textColor, shadowColor));
	pauseMenu->Append(new GuiButton(sf::FloatRect(lx + d, ly + d*2 + h, w, h),
		L"��������� � ����", ResourceManager::GetMainFont(), 24,
		[](const sf::Event&) { SetPause(false); },
		fillColor, textColor, outlineColor, shadowColor));
	pauseMenu->Append(new GuiButton(sf::FloatRect(lx + d, ly + d*3 + h*2, w, h),
		L"��������� ����", ResourceManager::GetMainFont(), 24,
		[](const sf::Event&) {},
		fillColor, textColor, outlineColor, shadowColor));
	pauseMenu->Append(new GuiButton(sf::FloatRect(lx + d, ly + d*4 + h*3, w, h),
		L"����� � ������� ����", ResourceManager::GetMainFont(), 24,
		[](const sf::Event&) { SceneManager::ChangeScene<SceneMainMenu>(); },
		fillColor, textColor, outlineColor, shadowColor));

	const float n = 5, m = 3, s = 100.f,
		iw = s*n + d*(n+1), ih = s*m + d*(m+1) + s, ew = iw, eh = s*2 + d*2,
		ix = d, iy = hwh - (ih + d + eh) / 2, ex = ix, ey = iy + ih + d,
		x0 = ix + d, y0 = iy + s + d, x1 = ex + d, y1 = ey + s + d;
	inventory = new GuiList(sf::FloatRect(ix, iy, iw, ih),
		fillColor, outlineColor);
	inventory->Append(new GuiText(
		sf::FloatRect(ix, iy, iw, s),
		L"���������", ResourceManager::GetMainFont(), 48,
		sf::Color::White, sf::Color(128, 128, 128)));
	for (int x = 0; x < n; x++)
		for (int y = 0; y < m; y++)
			inventory->Append(new GuiItemSlot(
				sf::FloatRect(x0 + x * (s + d), y0 + y * (s + d), s, s),
				fillColor, textColor, *Level::GetItems()[0], 1,
				outlineColor, shadowColor));
	equipment = new GuiList(sf::FloatRect(ex, ey, ew, eh),
		fillColor, outlineColor);
	equipment->Append(new GuiText(
		sf::FloatRect(ex, ey, ew, s),
		L"����������", ResourceManager::GetMainFont(), 48,
		sf::Color::White, sf::Color(128, 128, 128)));
	for (int x = 0; x < n; x++)
		equipment->Append(new GuiItemSlot(
			sf::FloatRect(x1 + x * (s + d), y1, s, s),
			fillColor, textColor, *Level::GetItems()[0], 1,
			outlineColor, shadowColor));
}

SceneGame::~SceneGame()
{
	delete level;
	delete interText;
	delete pauseMenu;
	delete inventory;
	delete equipment;
	Item::Shutdown();
}

void SceneGame::ProcessEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape)
			if (!isInvMenu) isPaused = !isPaused;
			else isInvMenu = false;
		else if (!isPaused && event.key.code == sf::Keyboard::E)
			isInvMenu = !isInvMenu;
	isInterTextVisible = false;
	if (!isPaused && !isInvMenu)
		level->ProcessEvent(event);
	if (isPaused) pauseMenu->ProcessEvent(event);
	if (isInvMenu)
	{
		inventory->ProcessEvent(event);
		equipment->ProcessEvent(event);
	}
}

void SceneGame::Update(sf::Time deltaTime)
{
	if (!isPaused && !isInvMenu)
	{
		level->Update(deltaTime);
		if (isInterTextVisible)
			interText->Update(deltaTime);
		if (isInvMenu)
		{
			inventory->Update(deltaTime);
			equipment->Update(deltaTime);
		}
	} else pauseMenu->Update(deltaTime);
}

void SceneGame::RenderGUI(sf::RenderWindow *window)
{
	if (isInterTextVisible)
		interText->Render(window);
	if (isPaused) pauseMenu->Render(window);
	if (isInvMenu)
	{
		inventory->Render(window);
		equipment->Render(window);
	}
}

void SceneGame::RenderSFML(sf::RenderWindow *window)
{
	level->RenderSFML(window);
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