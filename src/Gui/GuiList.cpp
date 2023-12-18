#include "GuiList.h"
#include "GuiItemSlot.h"
#include "../Entity/Player.h"
#include "../Tile/TileChest.h"
#include "GuiText.h"
#include "../GameManager.h"
#include "../Scene/SceneGame.h"
#include "../Scene/SceneBattle.h"

GuiList::GuiList(sf::FloatRect dims, bool isInventory,
	sf::Color fillColor, sf::Color outlineColor)
	: Gui(dims), rect(dims, fillColor, outlineColor),
	isInventory(isInventory), showItemPopup(false), itemPopup(nullptr)
{
	if (isInventory)
	{
		itemPopup = new GuiList(sf::FloatRect(100.f, 100.f, 100.f, 100.f));
		itemPopup->Append(new GuiText(sf::FloatRect(), "", 18, false));
		itemPopup->Append(new GuiText(sf::FloatRect(0.f, 50.f, 0.f, 0.f), "", 18, false));
		itemPopup->Minimize();
	}
}

GuiList::~GuiList()
{
	for (Gui *element : children)
		delete element;
	if (itemPopup != nullptr) delete itemPopup;
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
	if (isInventory) UpdateItemPopup();
}

void GuiList::Render(sf::RenderWindow *window)
{
	rect.Render(window);
	for (Gui *element : children)
		element->Render(window);
	if (showItemPopup)
		if (dynamic_cast<SceneGame*>(SceneManager::GetCurrentScene()))
			SceneGame::RenderOnTop(itemPopup);
		else SceneBattle::RenderOnTop(itemPopup);
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

void GuiList::Minimize()
{
	sf::Vector2f newSize = sf::Vector2f(0.f, 0.f),
		startPos = dimensions.getPosition();
	for (Gui *gui : children)
	{
		sf::FloatRect relDims = sf::FloatRect(
			gui->dimensions.getPosition() - startPos, gui->dimensions.getSize());
		if (relDims.left + relDims.width > newSize.x)
			newSize = sf::Vector2f(relDims.left + relDims.width, newSize.y);
		if (relDims.top + relDims.height > newSize.y)
			newSize = sf::Vector2f(newSize.x, relDims.top + relDims.height);
	}
	dimensions = sf::FloatRect(startPos, newSize);
	rect.SetDimensions(dimensions);
}

void GuiList::SetDimensions(sf::FloatRect dims)
{
	dimensions = dims;
	rect.SetDimensions(dims);
}

void GuiList::UpdateItemPopup()
{
	showItemPopup = false;
	for (Gui *gui : children)
	{
		GuiItemSlot *slot = dynamic_cast<GuiItemSlot*>(gui);
		if (slot == nullptr) continue;
		if (slot->item != nullptr && slot->IsMouseOver() &&
			!slot->IsPressed() && !slot->ShouldDrag())
		{
			showItemPopup = true;
			GuiText *name = dynamic_cast<GuiText*>(itemPopup->children[0]),
				*desc = dynamic_cast<GuiText*>(itemPopup->children[1]);
			name->SetString(slot->item->GetName());
			name->Stretch();
			desc->SetString(slot->item->GetDescription());
			desc->Stretch();
			itemPopup->Minimize();
			itemPopup->SetDimensions(sf::FloatRect(
				itemPopup->dimensions.left, itemPopup->dimensions.top,
				itemPopup->dimensions.width + 25.f, itemPopup->dimensions.height));
			sf::Vector2f mPos = (sf::Vector2f)sf::Mouse::getPosition(
				*GameManager::GetWindow()) + sf::Vector2f(15.f, 15.f);
			sf::Vector2f size = itemPopup->dimensions.getSize() + sf::Vector2f(0.f, 25.f),
				deltaPos = sf::Vector2f();
			if ((mPos + size).x > GameManager::WindowWidth())
				deltaPos = sf::Vector2f(-size.x, 0.f);
			if ((mPos + size).y > GameManager::WindowHeight())
				deltaPos = sf::Vector2f(deltaPos.x, -size.y);
			itemPopup->SetDimensions(sf::FloatRect(mPos + deltaPos, size));
			name->SetDimensions(sf::FloatRect(
				mPos + sf::Vector2f(25.f, 25.f) + deltaPos, name->dimensions.getSize()));
			desc->SetDimensions(sf::FloatRect(
				mPos + sf::Vector2f(25.f, 75.f) + deltaPos, desc->dimensions.getSize()));
			break;
		}
	}
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
		true, Gui::ButtonFillColor, Gui::ButtonOutlineColor);
	inventoryGui->Append(new GuiText(
		sf::FloatRect(ix, iy, iw, s), L"Инвентарь", 48));
	for (int y = 0; y < m; y++)
		for (int x = 0; x < n; x++)
			inventoryGui->Append(new GuiItemSlot(
				sf::FloatRect(x0 + x * (s + d), y0 + y * (s + d), s, s),
				nullptr, y * 5 + x, SlotType::Any, Player::GetItem(y * 5 + x)));
	return inventoryGui;
}
