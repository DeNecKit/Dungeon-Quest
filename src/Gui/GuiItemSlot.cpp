#include "GuiItemSlot.h"
#include "../Scene/SceneGame.h"

GuiItemSlot::GuiItemSlot(sf::FloatRect dims,
	sf::Color fillColor, sf::Color textColor, SlotType type,
	Item *item, sf::Color outlineColor, sf::Color shadowColor)
	: Gui(dims), type(type), item(item), origPos(dimensions.getPosition()),
	rect(dims, fillColor, outlineColor),
	click(dims, [](const sf::Event&) {}, true,
		new GuiDraggable(sf::milliseconds(64))) {}

void GuiItemSlot::ProcessEvent(const sf::Event &event)
{
	click.ProcessEvent(event);
}

void GuiItemSlot::Update(sf::Time deltaTime)
{
	click.Update(deltaTime);
	if (item != nullptr)
	{
		sf::Vector2i curMousePos = sf::Mouse::getPosition(*GameManager::GetWindow());
		if (click.ShouldDrag())
			dimensions = sf::FloatRect(
				dimensions.getPosition().x + (curMousePos - lastMousePos).x,
				dimensions.getPosition().y + (curMousePos - lastMousePos).y,
				dimensions.width, dimensions.height);
		else dimensions = sf::FloatRect(origPos, dimensions.getSize());
		lastMousePos = curMousePos;

		if (click.DragReleased())
			for (Gui* gui : SceneGame::GetInventoryGui())
				if (gui != this && gui->IsMouseOver())
				{
					GuiItemSlot* other = (GuiItemSlot*)gui;
					SlotType otherType = other->GetType();
					ItemType otherItemType = other->item == nullptr
						? ItemType::None : other->item->GetType();
					if ((type == SlotType::Any ||
						(ItemType)type == otherItemType ||
						otherItemType == ItemType::None) &&
						(other->GetType() == SlotType::Any ||
						(ItemType)otherType == item->GetType()))
					{
						Item* tmp = other->item;
						other->item = item;
						item = tmp;
						break;
					}
				}
	}
}

void GuiItemSlot::Render(sf::RenderWindow *window)
{
	rect.Render(window);
	if (item != nullptr)
	{
		sprite = item->GetSprite();
		int spSize = (int)ItemTemplate::GetSize();
		sprite.setPosition(
			dimensions.left + dimensions.width / 2.f - spSize / 2.f,
			dimensions.top + dimensions.height / 2.f - spSize / 2.f);
		if (click.ShouldDrag())
			SceneGame::RenderOnTop(&sprite);
		else window->draw(sprite);
	}
	if (!click.ShouldDrag()) click.Render(window);
}

SlotType GuiItemSlot::GetType()
{
	return type;
}