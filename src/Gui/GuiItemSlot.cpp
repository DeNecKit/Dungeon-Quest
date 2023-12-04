#include "GuiItemSlot.h"

GuiItemSlot::GuiItemSlot(sf::FloatRect dims, Item *item,
	sf::Color fillColor, sf::Color textColor,
	sf::Color outlineColor, sf::Color shadowColor)
	: Gui(dims), item(item), rect(dims, fillColor, outlineColor),
	click(dims, [](const sf::Event&) {}) {}

void GuiItemSlot::ProcessEvent(const sf::Event &event)
{
	click.ProcessEvent(event);
}

void GuiItemSlot::Update(sf::Time deltaTime)
{
}

void GuiItemSlot::Render(sf::RenderWindow *window)
{
	rect.Render(window);
	click.Render(window);
}