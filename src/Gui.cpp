#include "Gui.h"
#include "GuiStyle.h"
#include "GameManager.h"

Gui::Gui(sf::Vector2f pos, sf::Vector2f size,
	GuiStyle style, bool enabled)
	: pos(pos), size(size),
	  isEnabled(enabled), needsRefresh(true) {}

Gui::~Gui() {}

bool Gui::IsMouseOver()
{
	sf::Vector2i mPos = sf::Mouse::getPosition(*GameManager::GetWindow());
	int mx = mPos.x, my = mPos.y;
	int x = (int)pos.x, y = (int)pos.y,
		w = (int)size.x, h = (int)size.y;
	return mx >= x && mx <= x + w && my >= y && my <= y + h;
}