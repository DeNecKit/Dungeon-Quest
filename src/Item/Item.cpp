#include "Item.h"

Item::Item(ItemTemplate* itemTemplate, unsigned int count)
	: itemTemplate(itemTemplate), count(count)
{
	itemMemory->push_back(this);
}

sf::Sprite Item::GetSprite()
{
	return itemTemplate->GetSprite();
}

unsigned int Item::GetSize()
{
	return ItemTemplate::GetSize();
}

unsigned int Item::GetCount()
{
	return count;
}

ItemType Item::GetType()
{
	return itemTemplate == nullptr ? ItemType::None : itemTemplate->GetType();
}

ItemTemplate *Item::GetTemplate()
{
	return itemTemplate;
}

void Item::Use()
{
	itemTemplate->Click();
	count--;
}

Item* Item::Create(unsigned int itemTemplateId, unsigned int count)
{
	return new Item(ItemTemplate::GetItemTemplates()[itemTemplateId], count);
}

void Item::Delete(Item *item)
{
	for (int i = 0; i < itemMemory->size(); i++)
	{
		if (itemMemory->at(i) == item)
			itemMemory->at(i) = nullptr;
	}
	delete item;
}

sf::Sprite &Item::GetEquipmentSlotSprite(ItemType slot)
{
	return equipmentSlots->at(slot);
}

void Item::Init()
{
	itemMemory = new std::vector<Item*>();
	eqSlotsTexture = new sf::Texture();
	if (!eqSlotsTexture->loadFromFile("data/equipment-slots.png"))
		throw new std::exception();
	equipmentSlots = new std::map<ItemType, sf::Sprite>();
	for (int i = 0; i < 5; i++)
	{
		sf::Sprite s = sf::Sprite(*eqSlotsTexture, sf::IntRect(i*32, 0, 32, 32));
		float factor = GetSize() / 32.f;
		s.setScale(factor, factor);
		equipmentSlots->insert({ (ItemType)((int)ItemType::Sword + i), s });
	}
}

void Item::Shutdown()
{
	for (int i = 0; i < itemMemory->size(); i++)
	{
		Item *item = itemMemory->at(i);
		if (item != nullptr) delete item;
	}
	delete itemMemory;
	delete equipmentSlots;
	delete eqSlotsTexture;
}