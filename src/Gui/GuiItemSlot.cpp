#include "GuiItemSlot.h"
#include "../Scene/SceneGame.h"
#include "../Scene/SceneBattle.h"
#include "../Battle.h"
#include "../ResourceManager.h"

GuiItemSlot::GuiItemSlot(sf::FloatRect dims, TileChest* parentChest,
	unsigned int pos, SlotType type, Item* item)
	: Gui(dims), type(type), item(item), origPos(dimensions.getPosition()),
	rect(dims, Gui::ItemSlotFillColor, Gui::ItemSlotOutlineColor),
	pos(pos), parentChest(parentChest),
	click(dims, [](const sf::Event&) {}, true,
		new GuiDraggable(sf::milliseconds(32))),
	lastCount(item == nullptr ? 1 : item->GetCount()), countText(sf::FloatRect(
		dims.left + dims.width * 0.7f, dims.top + dims.height * 0.7f,
		dims.width * 0.2f, dims.height * 0.2f),
		"", 16, true, ResourceManager::GetMainFont(),
		Gui::TextColor, sf::Color::Black)
{
	if (lastCount > 1) countText.SetString(std::to_string(lastCount));
}

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
		{
			std::vector<Gui*> inventory;
			inventory = dynamic_cast<SceneGame*>(SceneManager::GetCurrentScene())
				? SceneGame::GetInventoryGui()
				: SceneBattle::GetInventoryGui();
			for (Gui *gui : inventory)
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
	if (item != nullptr)
	{
		if (lastCount != item->GetCount())
		{
			lastCount = item->GetCount();
			countText.SetString(lastCount > 1 ? std::to_string(lastCount) : "");
		}
		if (item->GetCount() == 0)
		{
			Item::Delete(item);
			item = nullptr;
			if (parentChest == nullptr)
				Player::SetItem(pos, nullptr);
			else throw new std::exception();
		}
	} else if (lastCount > 1) lastCount = 1;
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
			if (dynamic_cast<SceneGame*>(SceneManager::GetCurrentScene()))
				SceneGame::RenderOnTop(&sprite);
			else SceneBattle::RenderOnTop(&sprite);
		else window->draw(sprite);
	}
	if (!click.ShouldDrag())
	{
		if (lastCount > 1) countText.Render(window);
		click.Render(window);
	}
}

unsigned int GuiItemSlot::GetPos()
{
	return pos;
}