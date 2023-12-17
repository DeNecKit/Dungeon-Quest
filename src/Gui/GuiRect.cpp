#include "GuiRect.h"

GuiRect::GuiRect(sf::FloatRect dims, sf::Color fillColor,
	sf::Color outlineColor) : Gui(dims)
{
	rect = sf::RectangleShape(dimensions.getSize());
	rect.setPosition(dimensions.getPosition());
	rect.setFillColor(fillColor);
	rect.setOutlineThickness(4.f);
	rect.setOutlineColor(outlineColor);
}

void GuiRect::ProcessEvent(const sf::Event&) {}

void GuiRect::Update(sf::Time deltaTime) {}

void GuiRect::Render(sf::RenderWindow *window)
{
	window->draw(rect);
}

void GuiRect::ScaleSize(sf::Vector2f factors)
{
	rect.setSize(sf::Vector2f(
		dimensions.width * factors.x, dimensions.height * factors.y));
}

void GuiRect::SetDimensions(sf::FloatRect dims)
{
	dimensions = dims;
	rect.setPosition(dims.getPosition());
	rect.setSize(dims.getSize());
}