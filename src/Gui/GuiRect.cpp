#include "GuiRect.h"

GuiRect::GuiRect(sf::FloatRect dims, sf::Color fillColor,
	sf::Color outlineColor)
{
	rect = sf::RectangleShape(dims.getSize());
	rect.setPosition(dims.getPosition());
	rect.setFillColor(fillColor);
	rect.setOutlineThickness(4.f);
	rect.setOutlineColor(outlineColor);
}

void GuiRect::Render(sf::RenderWindow *window)
{
	window->draw(rect);
}