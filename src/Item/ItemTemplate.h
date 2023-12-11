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
		std::map<Stat, const int> stats =
			{{Stat::HP, 0}, {Stat::ATK, 0}, {Stat::DEF, 0}, {Stat::AGI, 0}});
	sf::Sprite GetSprite();
	sf::Texture* GetTileset();
	ItemType GetType();
	std::map<Stat, const int> GetStats();

	static void Init();
	static void Shutdown();
	static unsigned int GetSize();
	static std::vector<ItemTemplate*> GetItemTemplates();

protected:
	ItemType type;
	const sf::String &name;
	unsigned int textureId;
	std::map<Stat, const int> stats;

	static inline sf::Texture *tileset;
	static inline unsigned int size;
	static inline std::vector<ItemTemplate*>* itemTemplates;
};