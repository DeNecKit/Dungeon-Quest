#include "GuiProgressBar.h"

GuiProgressBar::GuiProgressBar(sf::FloatRect dims,
	sf::Color barClr, unsigned int& val, unsigned int maxVal)
	: Gui(dims), bar(dims, barClr), value(val), maxValue(maxVal),
	background(dims, sf::Color::Black, ButtonOutlineColor) {}

void GuiProgressBar::ProcessEvent(const sf::Event&) {}

void GuiProgressBar::Update(sf::Time deltaTime)
{
	bar.dimensions = sf::FloatRect(
		dimensions.left, dimensions.top,
		dimensions.width * maxValue / value, dimensions.height);
}

void GuiProgressBar::Render(sf::RenderWindow *window)
{
	background.Render(window);
	bar.Render(window);
}

sf::Vector2f GuiProgressBar::GetHealthBarSize()
{
	return sf::Vector2f(250.f, 25.f);
}