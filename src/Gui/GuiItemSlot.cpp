#include "GuiItemSlot.h"
#include "../Scene/SceneGame.h"
#include "../Scene/SceneBattle.h"
#include "../Battle.h"
#include "../ResourceManager.h"

GuiItemSlot::GuiItemSlot(sf::FloatRect dims, TileChest *parentChest,
	unsigned int pos, SlotType type, Item *item, bool isClickable)
	: Gui(dims), type(type), item(item), origPos(dimensions.getPosition()),
	rect(dims, Gui::ItemSlotFillColor, Gui::ItemSlotOutlineColor),
	pos(pos), parentChest(parentChest), isClickable(isClickable),
	click(dims, [](const sf::Event&) {}, true,
		new GuiDraggable(sf::milliseconds(100)), isClickable),
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
		&& !click.ShouldDrag() && Battle::Get() != nullptr) Battle::ChooseItem(item);
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
		else
		{
			dimensions = sf::FloatRect(origPos, dimensions.getSize());
			countText.SetDimensions(sf::FloatRect(
				dimensions.left + dimensions.width * 0.7f,
				dimensions.top + dimensions.height * 0.7f,
				dimensions.width * 0.2f, dimensions.height * 0.2f));
		}
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
						if (type > SlotType::Any || other->type > SlotType::Any)
							SceneGame::UpdateStatsText();
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
	int spSize = (int)ItemTemplate::GetSize();
	bool renderSlot = item == nullptr || click.ShouldDrag();
	if (item != nullptr)
	{
		sprite = item->GetSprite();
		sprite.setPosition(
			dimensions.left + dimensions.width / 2.f - spSize / 2.f,
			dimensions.top + dimensions.height / 2.f - spSize / 2.f);
		if (click.ShouldDrag())
		{
			if (dynamic_cast<SceneGame*>(SceneManager::GetCurrentScene()))
				SceneGame::RenderOnTop(&sprite);
			else SceneBattle::RenderOnTop(&sprite);
			if (lastCount > 1)
			{
				countText.SetDimensions(sf::FloatRect(
					dimensions.left + dimensions.width * 0.7f,
					dimensions.top + dimensions.height * 0.7f,
					dimensions.width * 0.2f, dimensions.height * 0.2f));
				if (dynamic_cast<SceneGame*>(SceneManager::GetCurrentScene()))
					SceneGame::RenderOnTop(&countText);
				else SceneBattle::RenderOnTop(&countText);
			}
		}
		else
		{
			window->draw(sprite);
			if (lastCount > 1)
			{
				countText.Render(window);
				countText.SetDimensions(sf::FloatRect(
					origPos.x + dimensions.width * 0.7f,
					origPos.y + dimensions.height * 0.7f,
					dimensions.width * 0.2f, dimensions.height * 0.2f));
			}
		}
	}
	if (type >= SlotType::Sword && renderSlot)
	{
		sf::Sprite s = Item::GetEquipmentSlotSprite((ItemType)type);
		s.setPosition(
			origPos.x + dimensions.width / 2.f - spSize / 2.f,
			origPos.y + dimensions.height / 2.f - spSize / 2.f);
		window->draw(s);
	}
	if (!click.ShouldDrag()) click.Render(window);
}

unsigned int GuiItemSlot::GetPos()
{
	return pos;
}

bool GuiItemSlot::IsPressed()
{
	return click.IsPressed();
}

bool GuiItemSlot::ShouldDrag()
{
	return click.ShouldDrag();
}