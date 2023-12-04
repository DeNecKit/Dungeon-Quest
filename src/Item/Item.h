#pragma once

#include <SFML/Graphics.hpp>
#include "../Gui/Gui.h"
#include "../Entity.h"
#include <map>

enum class ItemType
	{ Sword, Helmet, Chestplate, Leggings, Boots, Potion };

class Item
{
public:
	Item(ItemType type, const sf::String &name,
		unsigned int textureId,
		const int *stats = new int[] { 0, 0, 0, 0 });
	sf::Sprite GetSprite(sf::RenderWindow*);
	~Item();

	static void Init();
	static void Shutdown();

protected:
	ItemType type;
	const sf::String &name;
	unsigned int textureId;
	const int *stats;

	static inline sf::Texture *tileset;
	static inline unsigned int size = 75;
};