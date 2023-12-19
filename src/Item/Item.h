#pragma once

#include "ItemTemplate.h"
#include <vector>
#include <map>

class Item
{
public:
	Item(ItemTemplate *itemTemplate, unsigned int count);
	Item(const Item&);
	sf::Sprite GetSprite();
	unsigned int GetCount();
	void SetCount(unsigned int count);
	ItemType GetType();
	ItemTemplate *GetTemplate();
	bool IsUsable();
	void Use();
	const sf::String &GetName();
	const sf::String &GetDescription();

	static unsigned int GetSize();
	static Item *Create(unsigned int itemTemplateId,
		unsigned int count = 1);
	static void Delete(Item *item);
	static sf::Sprite &GetEquipmentSlotSprite(ItemType slot);
	static void Init();
	static void Clear();
	static void Shutdown();

private:
	ItemTemplate *itemTemplate;
	unsigned int count;

	static inline std::vector<Item*> *itemMemory;
	static inline sf::Texture *eqSlotsTexture;
	static inline std::map<ItemType, sf::Sprite> *equipmentSlots;
};