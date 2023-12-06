#include "Item.h"

Item::Item(ItemType type, const sf::String &name,
	unsigned int textureId, std::map<Stat, const int> stats)
	: type(type), name(name), textureId(textureId), stats(stats) {}

sf::Sprite Item::GetSprite()
{
	int x = textureId % 5 * 32,
		y = textureId / 5 * 32;
	sf::Sprite s(*tileset, sf::IntRect(x, y, 32, 32));
	float factor = size / 32.f;
	s.setScale(factor, factor);
	return s;
}

void Item::Init()
{
	size = 75 * GameManager::ResCoefX();
	emptyItem = new Item(ItemType::None, "none", 0, {});
	tileset = new sf::Texture();
	if (!tileset->loadFromFile("data/items.png"))
		throw new std::exception();
}

void Item::Shutdown()
{
	delete emptyItem;
	delete tileset;
}

Item Item::GetEmptyItem()
{
	return *emptyItem;
}

unsigned int Item::GetSize()
{
	return size;
}