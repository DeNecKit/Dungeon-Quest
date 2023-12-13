#include "GuiList.h"
#include "GuiItemSlot.h"
#include "../Entity/Player.h"
#include "../Tile/TileChest.h"
#include "GuiText.h"

GuiList::GuiList(sf::FloatRect dims,
	sf::Color fillColor, sf::Color outlineColor)
	: Gui(dims), rect(dims, fillColor, outlineColor) {}

GuiList::~GuiList()
{
	for (Gui *element : children)
		delete element;
}

void GuiList::ProcessEvent(const sf::Event &event)
{
	for (Gui *element : children)
		element->ProcessEvent(event);
}

void GuiList::Update(sf::Time deltaTime)
{
	for (Gui *element : children)
		element->Update(deltaTime);
}

void GuiList::Render(sf::RenderWindow *window)
{
	rect.Render(window);
	for (Gui *element : children)
		element->Render(window);
}

void GuiList::Append(Gui *element)
{
	children.push_back(element);
}

std::vector<Gui*> GuiList::GetChildren()
{
	return children;
}

void GuiList::SetItem(unsigned int pos, Item *item)
{
	dynamic_cast<GuiItemSlot*>(children[pos+1])->item = item;
}

void GuiList::SetParent(unsigned int pos, TileChest *parentChest)
{
	GuiItemSlot* slot = dynamic_cast<GuiItemSlot*>(children[pos+1]);
	slot->parentChest = parentChest;
}

GuiList *GuiList::CreatePlayerInventory()
{
	const float hww = 1920.f / 2, hwh = 1080.f / 2,
		n = 5, m = 3, s = 100.f, d = 50.f,
		iw = s * n + d * (n + 1), ih = s * m + d * (m + 1) + s,
		ew = iw, eh = s * 2 + d * 2,
		cw = iw, ch = ih,
		ix = d, iy = hwh - (ih + d + eh) / 2,
		ex = ix, ey = iy + ih + d,
		cx = hww * 2 - cw - d, cy = iy,
		x0 = ix + d, y0 = iy + s + d,
		x1 = ex + d, y1 = ey + s + d,
		x2 = cx + d, y2 = cy + s + d;
	GuiList *inventoryGui = new GuiList(sf::FloatRect(ix, iy, iw, ih),
		Gui::ButtonFillColor, Gui::ButtonOutlineColor);
	inventoryGui->Append(new GuiText(
		sf::FloatRect(ix, iy, iw, s), L"Инвентарь", 48));
	for (int y = 0; y < m; y++)
		for (int x = 0; x < n; x++)
			inventoryGui->Append(new GuiItemSlot(
				sf::FloatRect(x0 + x * (s + d), y0 + y * (s + d), s, s),
				nullptr, y * 5 + x, SlotType::Any, Player::GetItem(y * 5 + x)));
	return inventoryGui;
}
