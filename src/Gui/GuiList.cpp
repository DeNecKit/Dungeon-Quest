#include "GuiList.h"
#include "GuiItemSlot.h"
#include "../Entity/Player.h"
#include "../Tile/TileChest.h"

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