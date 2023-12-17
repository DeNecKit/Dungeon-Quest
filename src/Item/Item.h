#pragma once

#include "ItemTemplate.h"
#include <vector>
#include <map>

class Item
{
public:
	Item(ItemTemplate *itemTemplate, unsigned int count);
	sf::Sprite GetSprite();
	unsigned int GetCount();
	ItemType GetType();
	ItemTemplate *GetTemplate();
	void Use();
	const sf::String &GetName();
	const sf::String &GetDescription();

	static unsigned int GetSize();
	static Item *Create(unsigned int itemTemplateId,
		unsigned int count = 1);
	static void Delete(Item *item);
	static sf::Sprite &GetEquipmentSlotSprite(ItemType slot);
	static void Init();
	static void Shutdown();

private:
	ItemTemplate *itemTemplate;
	unsigned int count;

	static inline std::vector<Item*> *itemMemory;
	static inline sf::Texture *eqSlotsTexture;
	static inline std::map<ItemType, sf::Sprite> *equipmentSlots;
};