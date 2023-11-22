#include "ResourceManager.h"

sf::Font *ResourceManager::GetMainFont()
{
	if (mainFont == nullptr)
	{
		mainFont = new sf::Font();
		if (!mainFont->loadFromFile("data/font.ttf"))
			throw new std::exception();
	}
	return mainFont;
}

void ResourceManager::Shutdown()
{
	if (mainFont != nullptr)
		delete mainFont;
}