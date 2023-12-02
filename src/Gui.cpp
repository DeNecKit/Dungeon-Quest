#include "Gui.h"
#include "GuiStyle.h"
#include "GameManager.h"

Gui::Gui(sf::FloatRect dims) : IsEnabled(true)
{
	dims = sf::FloatRect(
		dims.left * GameManager::ResCoefX(),
		dims.top * GameManager::ResCoefY(),
		dims.width * GameManager::ResCoefX(),
		dims.height * GameManager::ResCoefY());
	dimensions = dims;
}

bool Gui::IsMouseOver()
{
	sf::Vector2i mPos = sf::Mouse::getPosition(*GameManager::GetWindow());
	int mx = mPos.x, my = mPos.y;
	int x = (int)dimensions.left, y = (int)dimensions.top,
		w = (int)dimensions.width, h = (int)dimensions.height;
	return mx >= x && mx <= x + w && my >= y && my <= y + h;
}