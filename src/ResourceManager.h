#pragma once

#include <SFML/Graphics.hpp>

class ResourceManager
{
public:
	static sf::Font *GetMainFont();
	static void Shutdown();
private:
	static inline sf::Font *mainFont;
};