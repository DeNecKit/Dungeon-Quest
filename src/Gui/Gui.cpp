#include "Gui.h"
#include "../GameManager.h"

Gui::Gui(sf::FloatRect dims)
{
	dims = sf::FloatRect(
		dims.left * GameManager::ResCoefX(),
		dims.top * GameManager::ResCoefY(),
		dims.width * GameManager::ResCoefX(),
		dims.height * GameManager::ResCoefY());
	dimensions = dims;
}

Gui::~Gui() {}

bool Gui::IsMouseOver()
{
	return GameManager::IsMouseOver(dimensions);
}