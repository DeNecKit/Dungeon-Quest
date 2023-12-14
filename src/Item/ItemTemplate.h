#pragma once

#include <SFML/Graphics.hpp>
#include "../Gui/Gui.h"
#include "../Entity/Entity.h"
#include "../GameManager.h"
#include <map>

enum class ItemType
	{ None, Sword, Helmet, Chestplate, Leggings, Boots, Potion, Key };

class ItemTemplate
{
public:
	ItemTemplate(ItemType type, const sf::String &name,
		unsigned int textureId,
		std::map<Stat, const int> stats = nullStats,
		bool isUsable = false, void (*onClick)() = []() {});
	sf::Sprite GetSprite();
	sf::Texture* GetTileset();
	ItemType GetType();
	std::map<Stat, const int> GetStats();
	bool IsUsable();
	void Click();

	static void Init();
	static void Shutdown();
	static unsigned int GetSize();
	static std::vector<ItemTemplate*> GetItemTemplates();
	static std::map<Stat, const int> GetNullStats();

protected:
	ItemType type;
	const sf::String &name;
	unsigned int textureId;
	std::map<Stat, const int> stats;
	bool isUsable;
	void (*onClick)();

	static inline sf::Texture *tileset;
	static inline unsigned int size;
	static inline std::vector<ItemTemplate*>* itemTemplates;
	static inline std::map<Stat, const int> nullStats
		= { {Stat::HP, 0}, {Stat::ATK, 0}, {Stat::DEF, 0}, {Stat::AGI, 0} };
};