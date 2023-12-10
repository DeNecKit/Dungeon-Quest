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
	return itemTemplate->GetSize();
}

unsigned int Item::GetCount()
{
	return count;
}

ItemType Item::GetType()
{
	return itemTemplate == nullptr ? ItemType::None : itemTemplate->GetType();
}

Item* Item::Create(unsigned int itemTemplateId, unsigned int count)
{
	return new Item(ItemTemplate::GetItemTemplates()[itemTemplateId], count);
}

void Item::Init()
{
	itemMemory = new std::vector<Item*>();
}

void Item::Shutdown()
{
	//for (Item *item : itemMemory)
		//delete item;
	//itemMemory.clear();
	for (int i = 0; i < itemMemory->size(); i++)
	{
		Item *item = itemMemory->at(i);
		delete item;
	}
	delete itemMemory;
}