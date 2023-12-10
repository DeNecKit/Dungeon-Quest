#pragma once

#include "ItemTemplate.h"
#include <vector>

class Item
{
public:
	Item(ItemTemplate *itemTemplate, unsigned int count);
	sf::Sprite GetSprite();
	unsigned int GetSize();
	unsigned int GetCount();
	ItemType GetType();

	static Item *Create(unsigned int itemTemplateId,
		unsigned int count = 1);
	static void Init();
	static void Shutdown();

private:
	ItemTemplate *itemTemplate;
	unsigned int count;

	static inline std::vector<Item*> *itemMemory;
};