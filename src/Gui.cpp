#include "Gui.h"
#include "GuiStyle.h"
#include "GameManager.h"

Gui::Gui(GuiStyle style, bool enabled)
	: style(style), isEnabled(enabled),
	needsRefresh(true) {}

Gui::~Gui() {}

bool Gui::IsMouseOver()
{
	sf::Vector2i mPos = sf::Mouse::getPosition(*GameManager::GetWindow());
	int mx = mPos.x, my = mPos.y;
	int x = style.pos.x, y = style.pos.y,
		w = style.size.x, h = style.size.y;
	return mx >= x && mx <= x + w && my >= y && my <= y + h;
}