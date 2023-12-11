#include "GuiButton.h"
#include "../GameManager.h"

GuiButton::GuiButton(sf::FloatRect dims, const sf::String &str,
	unsigned int chSize, void (*onClick)(const sf::Event&), sf::Font *font)
	: Gui(dims), rect(dims, ButtonFillColor, ButtonOutlineColor),
	text(dims, str, chSize, font),
	click(dims, onClick) {}

void GuiButton::ProcessEvent(const sf::Event &event)
{
	click.ProcessEvent(event);
}

void GuiButton::Update(sf::Time deltaTime) {}

void GuiButton::Render(sf::RenderWindow *window)
{
	rect.Render(window);
	text.Render(window);
	click.Render(window);
}