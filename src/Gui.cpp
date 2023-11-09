#include "Gui.h"

GuiStyle::GuiStyle(unsigned int posX, unsigned int posY,
	unsigned int sizeX, unsigned int sizeY,
	sf::Color backgroundColor = sf::Color(48, 49, 52),
	sf::Color outlineColor = sf::Color(32, 33, 36),
	sf::Color textColor = sf::Color::Black,
	float outlineThickness = 1.f)
	: posX(posX), posY(posY), sizeX(sizeX), sizeY(sizeY),
	backgroundColor(backgroundColor), outlineColor(outlineColor),
	textColor(textColor), outlineThickness(outlineThickness) {}


Gui::Gui(GuiStyle style, bool enabled = true)
	: style(style), isEnabled(enabled)
{
	needsRefresh = true;
}


GuiClickable::GuiClickable(GuiStyle style, bool enabled = true)
	: Gui(style, enabled) {};

void GuiClickable::ProcessEvent(const sf::Event &event)
{
	if (event.type == sf::Event::MouseButtonPressed)
		OnClick(event);
}


GuiButton::GuiButton(GuiStyle style, bool enabled = true)
	: Gui(style, enabled) {}