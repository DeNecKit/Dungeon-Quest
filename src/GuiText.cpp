#include "GuiText.h"

GuiText::GuiText(sf::Vector2f pos,
	GuiStyle style, const sf::String &str, sf::Font *font,
	unsigned int chSize, bool enabled)
	: Gui(pos, sf::Vector2f(), style, enabled)
{
	text.setPosition(pos);
	text.setFont(*font);
	text.setString(str);
	text.setCharacterSize(chSize * 4 / 3);
	text.setFillColor(style.textColor);
}

void GuiText::ProcessEvent(const sf::Event&) {}

void GuiText::Update(float deltaTime) {}

void GuiText::Render(sf::RenderWindow *window)
{
	window->draw(text);
}