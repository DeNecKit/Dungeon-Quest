#include "ItemTemplate.h"
#include "../Entity/Player.h"
#include "../Level.h"
#include <cmath>

ItemTemplate::ItemTemplate(ItemType type, sf::String name,
	unsigned int textureId, std::map<Stat, const int> stats,
	bool isUsable, void (*onClick)())
	: type(type), name(name), textureId(textureId), description(nullptr),
	stats(stats), isUsable(isUsable), onClick(onClick) {}

ItemTemplate::~ItemTemplate()
{
	if (description != nullptr) delete description;
}

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

bool ItemTemplate::IsUsable()
{
	return isUsable;
}

void ItemTemplate::Click()
{
	onClick();
}

const sf::String &ItemTemplate::GetName()
{
	return name;
}

const sf::String &ItemTemplate::GetDescription()
{
	if (description == nullptr)
		switch (type)
		{
		case ItemType::Potion:
			switch (textureId)
			{
			case 30:
				description = new sf::String(L"Восстанавливает 15 очков здоровья");
				break;
			default: throw new std::exception();
			}
			break;
		case ItemType::Key:
			description = new sf::String(L"Ключ для выходной двери уровня");
			break;
		default:
			description = new sf::String();
			bool added = false;
			for (auto &[statType, stat] : stats)
				if (stat != 0)
				{
					if (added) *description += "\n";
					else added = true;
					*description += (stat > 0 ? "+" : "-") +
						std::to_string(std::abs(stat)) + statNames->at(statType);
				}
			break;
		}
	return *description;
}

void ItemTemplate::Init()
{
	statNames = new std::map<Stat, sf::String>({
		{Stat::HP, L" к макс. очкам здоровья"},
		{Stat::ATK, L" к атаке"}, {Stat::DEF, L" к защите"},
		{Stat::AGI, L" к ловкости"} });
	size = (int)(75 * GameManager::ResCoefX());
	tileset = new sf::Texture();
	if (!tileset->loadFromFile("data/items.png"))
		throw new std::exception();
	itemTemplates = new std::vector<ItemTemplate*>({
		new ItemTemplate(ItemType::Sword, L"Рыцарский меч", 0,
			{{Stat::HP, 0},{Stat::ATK, 100},{Stat::DEF, 0},{Stat::AGI, 0}}),
		new ItemTemplate(ItemType::Helmet, L"Кожанный шлем", 10,
			{{Stat::HP, 1},{Stat::ATK, 0},{Stat::DEF, 1},{Stat::AGI, 0}}),
		new ItemTemplate(ItemType::Chestplate, L"Кожанный нагрудник", 11,
			{{Stat::HP, 5},{Stat::ATK, 0},{Stat::DEF, 3},{Stat::AGI, 0}}),
		new ItemTemplate(ItemType::Leggings, L"Кожанные поножи", 12,
			{{Stat::HP, 3},{Stat::ATK, 0},{Stat::DEF, 2},{Stat::AGI, 0}}),
		new ItemTemplate(ItemType::Boots, L"Кожанные ботинки", 13,
			{{Stat::HP, 1},{Stat::ATK, 0},{Stat::DEF, 1},{Stat::AGI, 0}}),
		new ItemTemplate(ItemType::Sword, L"Королевский меч", 1,
			{{Stat::HP, 0},{Stat::ATK, 16},{Stat::DEF, 1},{Stat::AGI, 0}}),
		new ItemTemplate(ItemType::Key, L"Ключ", 34),
		new ItemTemplate(ItemType::Potion, L"Зелье лечения", 30,
			nullStats, true, []() { Player::Heal(15); }),
		new ItemTemplate(ItemType::Sword, L"Магический меч", 2,
			{{Stat::HP, 0}, {Stat::ATK, 24}, {Stat::DEF, -5}, {Stat::AGI, 5}}),
		new ItemTemplate(ItemType::Sword, L"Меч адского камня", 3,
			{{Stat::HP, -15}, {Stat::ATK, 30}, {Stat::DEF, 0}, {Stat::AGI, 0}})
	});
}

void ItemTemplate::Shutdown()
{
	delete statNames;
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

std::map<Stat, const int> ItemTemplate::GetNullStats()
{
	return nullStats;
}

ItemTemplate *ItemTemplate::Get(unsigned int index)
{
	return (*itemTemplates)[index];
}
