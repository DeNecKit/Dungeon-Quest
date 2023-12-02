#include "Gui.h"
#include "GuiStyle.h"
#include "GameManager.h"

Gui::Gui(sf::FloatRect dimensions) : IsEnabled(true)
{
	dimensions = sf::FloatRect(
		dimensions.left * GameManager::ResCoefX(),
		dimensions.top * GameManager::ResCoefY(),
		dimensions.width * GameManager::ResCoefX(),
		dimensions.height * GameManager::ResCoefY());
	this->dimensions = dimensions;
}

bool Gui::IsMouseOver()
{
	sf::Vector2i mPos = sf::Mouse::getPosition(*GameManager::GetWindow());
	int mx = mPos.x, my = mPos.y;
	int x = (int)dimensions.left, y = (int)dimensions.top,
		w = (int)dimensions.width, h = (int)dimensions.height;
	return mx >= x && mx <= x + w && my >= y && my <= y + h;
}