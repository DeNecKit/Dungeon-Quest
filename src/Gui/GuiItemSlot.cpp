#include "GuiItemSlot.h"
#include "../Scene/SceneGame.h"
#include "../Battle.h"

GuiItemSlot::GuiItemSlot(sf::FloatRect dims, TileChest *parentChest,
	unsigned int pos, SlotType type, Item *item)
	: Gui(dims), type(type), item(item), origPos(dimensions.getPosition()),
	rect(dims, Gui::ItemSlotFillColor, Gui::ItemSlotOutlineColor),
	pos(pos), parentChest(parentChest),
	click(dims, [](const sf::Event&) {}, true,
		new GuiDraggable(sf::milliseconds(32))) {}

void GuiItemSlot::ProcessEvent(const sf::Event &event)
{
	if (click.IsPressed() && event.type == sf::Event::MouseButtonReleased
		&& Battle::Get() != nullptr) Battle::ChooseItem(item);
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
				if (gui != this && dynamic_cast<GuiItemSlot*>(gui)
					&& gui->IsMouseOver())
				{
					GuiItemSlot* other = (GuiItemSlot*)gui;
					SlotType otherType = other->type;
					ItemType otherItemType = other->item == nullptr
						? ItemType::None : other->item->GetType();
					if ((type == SlotType::Any ||
						(ItemType)type == otherItemType ||
						otherItemType == ItemType::None) &&
						(other->type == SlotType::Any ||
						(ItemType)otherType == item->GetType()))
					{
						Item *tmp = other->item;
						other->item = item;
						if (other->parentChest == nullptr)
							Player::SetItem(other->GetPos(),  item);
						else other->parentChest->SetItem(other->GetPos(), item);
						item = tmp;
						if (parentChest == nullptr)
							Player::SetItem(pos, tmp);
						else parentChest->SetItem(pos, tmp);
					}
					break;
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

unsigned int GuiItemSlot::GetPos()
{
	return pos;
}