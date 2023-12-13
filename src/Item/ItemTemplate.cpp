#include "ItemTemplate.h"

ItemTemplate::ItemTemplate(ItemType type, const sf::String &name,
	unsigned int textureId, std::map<Stat, const int> stats)
	: type(type), name(name), textureId(textureId), stats(stats) {}

sf::Sprite ItemTemplate::GetSprite()
{
	int x = textureId % 5 * 32,
		y = textureId / 5 * 32;
	sf::Sprite s(*tileset, sf::IntRect(x, y, 32, 32));
	float factor = size / 32.f;
	s.setScale(factor, factor);
	return s;
}

sf::Texture* ItemTemplate::GetTileset()
{
	return tileset;
}

ItemType ItemTemplate::GetType()
{
	return type;
}

std::map<Stat, const int> ItemTemplate::GetStats()
{
	return stats;
}

void ItemTemplate::Init()
{
	size = (int)(75 * GameManager::ResCoefX());
	tileset = new sf::Texture();
	if (!tileset->loadFromFile("data/items.png"))
		throw new std::exception();
	itemTemplates = new std::vector<ItemTemplate*>({
		new ItemTemplate(ItemType::Sword, L"Рыцарский меч", 0,
			{{Stat::HP, 0},{Stat::ATK, 10},{Stat::DEF, 0},{Stat::AGI, 0}}),
		new ItemTemplate(ItemType::Helmet, L"Кожанный шлем", 10,
			{{Stat::HP, 1},{Stat::ATK, 0},{Stat::DEF, 1},{Stat::AGI, 0}}),
		new ItemTemplate(ItemType::Chestplate, L"Кожанный нагрудник", 11,
			{{Stat::HP, 5},{Stat::ATK, 0},{Stat::DEF, 3},{Stat::AGI, 0}}),
		new ItemTemplate(ItemType::Leggings, L"Кожанные поножи", 12,
			{{Stat::HP, 3},{Stat::ATK, 0},{Stat::DEF, 2},{Stat::AGI, 0}}),
		new ItemTemplate(ItemType::Boots, L"Кожанные ботинки", 13,
			{{Stat::HP, 1},{Stat::ATK, 0},{Stat::DEF, 1},{Stat::AGI, 0}}),
		new ItemTemplate(ItemType::Sword, L"Королевский меч", 1,
			{{Stat::HP, 0},{Stat::ATK, 15},{Stat::DEF, 1},{Stat::AGI, 0}}),
		new ItemTemplate(ItemType::Key, L"Ключ", 34)
	});
}

void ItemTemplate::Shutdown()
{
	delete tileset;
	for (ItemTemplate* i : *itemTemplates)
		delete i;
	delete itemTemplates;
}


unsigned int ItemTemplate::GetSize()
{
	return size;
}

std::vector<ItemTemplate*> ItemTemplate::GetItemTemplates()
{
	return *itemTemplates;
}