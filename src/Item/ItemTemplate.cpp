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
			description = new sf::String(L"Восстанавливает " + std::to_wstring(
				textureId == 14 ? 15 : textureId == 19 ? 30 : 50) + L" очков здоровья");
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
		/*0*/ new ItemTemplate(ItemType::Sword, L"Рыцарский меч", 0,
			{{Stat::HP, 0},{Stat::ATK, 500},{Stat::DEF, 0},{Stat::AGI, 0}}),
		/*1*/ new ItemTemplate(ItemType::Helmet, L"Кожанный шлем", 10,
			{{Stat::HP, 1},{Stat::ATK, 0},{Stat::DEF, 1},{Stat::AGI, 0}}),
		/*2*/ new ItemTemplate(ItemType::Chestplate, L"Кожанный нагрудник", 11,
			{{Stat::HP, 5},{Stat::ATK, 0},{Stat::DEF, 3},{Stat::AGI, 0}}),
		/*3*/ new ItemTemplate(ItemType::Leggings, L"Кожанные поножи", 12,
			{{Stat::HP, 3},{Stat::ATK, 0},{Stat::DEF, 2},{Stat::AGI, 0}}),
		/*4*/ new ItemTemplate(ItemType::Boots, L"Кожанные ботинки", 13,
			{{Stat::HP, 1},{Stat::ATK, 0},{Stat::DEF, 1},{Stat::AGI, 0}}),
		/*5*/ new ItemTemplate(ItemType::Sword, L"Королевский меч", 1,
			{{Stat::HP, 0},{Stat::ATK, 16},{Stat::DEF, 1},{Stat::AGI, 0}}),
		/*6*/ new ItemTemplate(ItemType::Key, L"Ключ", 29),
		/*7*/ new ItemTemplate(ItemType::Potion, L"Малое лечебное зелье", 14,
			nullStats, true, []() { Player::Heal(15); }),
		/*8*/ new ItemTemplate(ItemType::Sword, L"Магический меч", 2,
			{{Stat::HP, 0},{Stat::ATK, 24},{Stat::DEF, -5},{Stat::AGI, 5}}),
		/*9*/ new ItemTemplate(ItemType::Sword, L"Меч адского камня", 3,
			{{Stat::HP, -15},{Stat::ATK, 30},{Stat::DEF, 0},{Stat::AGI, 0}}),
		/*10*/ new ItemTemplate(ItemType::Helmet, L"Шипованный шлем", 15,
			{{Stat::HP, 2},{Stat::ATK, 1},{Stat::DEF, 2},{Stat::AGI, 0}}),
		/*11*/ new ItemTemplate(ItemType::Chestplate, L"Шипованный нагрудник", 16,
			{{Stat::HP, 6},{Stat::ATK, 2},{Stat::DEF, 5},{Stat::AGI, -2}}),
		/*12*/ new ItemTemplate(ItemType::Leggings, L"Шипованные поножи", 17,
			{{Stat::HP, 5},{Stat::ATK, 1},{Stat::DEF, 3},{Stat::AGI, -1}}),
		/*13*/ new ItemTemplate(ItemType::Boots, L"Шипованные ботинки", 18,
			{{Stat::HP, 2},{Stat::ATK, 1},{Stat::DEF, 2},{Stat::AGI, 0}}),
		/*14*/ new ItemTemplate(ItemType::Sword, L"Убийца драконов", 4,
			{{Stat::HP, 0},{Stat::ATK, 30},{Stat::DEF, 15},{Stat::AGI, -10}}),
		/*15*/ new ItemTemplate(ItemType::Sword, L"Проклятый меч", 5,
			{{Stat::HP, -25},{Stat::ATK, 50},{Stat::DEF, -15},{Stat::AGI, -10}}),
		/*16*/ new ItemTemplate(ItemType::Sword, L"Меч тьмы", 6,
			{{Stat::HP, -10},{Stat::ATK, 42},{Stat::DEF, -5},{Stat::AGI, 0}}),
		/*17*/ new ItemTemplate(ItemType::Sword, L"Солнечный меч", 7,
			{{Stat::HP, 15},{Stat::ATK, 32},{Stat::DEF, 5},{Stat::AGI, 10}}),
		/*18*/ new ItemTemplate(ItemType::Sword, L"Меч звёздной пыли", 8,
			{{Stat::HP, 20},{Stat::ATK, 37},{Stat::DEF, 7},{Stat::AGI, 12}}),
		/*19*/ new ItemTemplate(ItemType::Sword, L"Космический меч", 9,
			{{Stat::HP, 25},{Stat::ATK, 45},{Stat::DEF, 10},{Stat::AGI, 15}}),
		/*20*/ new ItemTemplate(ItemType::Helmet, L"Железный шлем", 25,
			{{Stat::HP, 6},{Stat::ATK, 2},{Stat::DEF, 4},{Stat::AGI, -1}}),
		/*21*/ new ItemTemplate(ItemType::Chestplate, L"Железный нагрудник", 26,
			{{Stat::HP, 10},{Stat::ATK, 3},{Stat::DEF, 7},{Stat::AGI, -5}}),
		/*22*/ new ItemTemplate(ItemType::Leggings, L"Железные поножи", 27,
			{{Stat::HP, 7},{Stat::ATK, 3},{Stat::DEF, 6},{Stat::AGI, -2}}),
		/*23*/ new ItemTemplate(ItemType::Boots, L"Железные ботинки", 28,
			{{Stat::HP, 6},{Stat::ATK, 2},{Stat::DEF, 4},{Stat::AGI, -1}}),
		/*24*/ new ItemTemplate(ItemType::Potion, L"Среднее лечебное зелье", 19,
			nullStats, true, []() { Player::Heal(30); }),
		/*25*/ new ItemTemplate(ItemType::Potion, L"Большое лечебное зелье", 24,
			nullStats, true, []() { Player::Heal(50); })
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
