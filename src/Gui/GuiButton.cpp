#include "GuiButton.h"
#include "../GameManager.h"

GuiButton::GuiButton(sf::FloatRect dims, const sf::String &str,
	unsigned int chSize, void (*onClick)(Gui *self),
	sf::Color fillColor, sf::Color outlineColor, sf::Font *font)
	: Gui(dims), rect(dims, fillColor, outlineColor),
	text(dims, str, chSize, font),
	click(dims, onClick), enabled(true)
{
	disabledRect = sf::RectangleShape(dimensions.getSize());
	disabledRect.setPosition(dimensions.getPosition());
	disabledRect.setFillColor(sf::Color(127, 127, 127, 100));
}

void GuiButton::ProcessEvent(const sf::Event &event)
{
	if (enabled) click.ProcessEvent(event);
}

void GuiButton::Update(sf::Time deltaTime) {}

void GuiButton::Render(sf::RenderWindow *window)
{
	rect.Render(window);
	text.Render(window);
	if (enabled) click.Render(window);
	else window->draw(disabledRect);
}

void GuiButton::SetEnabled(bool enabled)
{
	this->enabled = enabled;
}

GuiClickable *GuiButton::GetClickable()
{
	return &click;
}