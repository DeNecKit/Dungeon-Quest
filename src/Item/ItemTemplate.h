#pragma once

#include <SFML/Graphics.hpp>
#include "../Gui/Gui.h"
#include "../Entity.h"
#include "../GameManager.h"
#include <map>

enum class ItemType
	{ None, Sword, Helmet, Chestplate, Leggings, Boots, Potion };

class ItemTemplate
{
public:
	ItemTemplate(ItemType type, const sf::String &name,
		unsigned int textureId,
		std::map<Stat, const int> stats =
			{{Stat::HP, 0}, {Stat::ATK, 0}, {Stat::DEF, 0}, {Stat::AGI, 0}});
	sf::Sprite GetSprite();

	static void Init();
	static void Shutdown();
	static ItemTemplate GetEmptyItem();
	static unsigned int GetSize();
	static std::vector<ItemTemplate*> GetItemTemplates();
	sf::Texture *GetTileset();

protected:
	ItemType type;
	const sf::String &name;
	unsigned int textureId;
	std::map<Stat, const int> stats;

	static inline sf::Texture *tileset;
	static inline unsigned int size;
	static inline const ItemTemplate *emptyItem;
	static inline std::vector<ItemTemplate*>* itemTemplates;
};