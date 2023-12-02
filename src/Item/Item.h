#pragma once

#include <SFML/Graphics.hpp>
#include "../Gui/Gui.h"

class Item
{
public:
	virtual void Render(sf::RenderWindow*) = 0;

protected:
	Gui *parent;

	static inline sf::Texture *tileset;
};