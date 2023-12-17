#include "GuiProgressBar.h"

GuiProgressBar::GuiProgressBar(sf::FloatRect dims,
	sf::Color barClr, unsigned int &val, unsigned int &maxVal,
	unsigned int chSize, sf::Font *font)
	: Gui(dims), bar(dims, barClr), value(val), maxValue(maxVal),
	background(dims, sf::Color::Black, ButtonOutlineColor),
	text(dims, "", chSize, font) {}

void GuiProgressBar::ProcessEvent(const sf::Event&) {}

void GuiProgressBar::Update(sf::Time deltaTime)
{
	bar.ScaleSize(sf::Vector2f((float)value / (float)maxValue, 1.f));
	text.SetString(std::to_string(value) + "/" + std::to_string(maxValue));
	text.Update(deltaTime);
}

void GuiProgressBar::Render(sf::RenderWindow *window)
{
	background.Render(window);
	bar.Render(window);
	text.Render(window);
}

sf::Vector2f GuiProgressBar::GetHealthBarSize()
{
	return sf::Vector2f(250.f, 30.f);
}