#include "GuiText.h"
#include "ResourceManager.h"

GuiText::GuiText(sf::Vector2f pos, sf::Vector2f size,
	GuiStyle style, const sf::String &str, sf::Font *font,
	unsigned int chSize, bool enabled)
	: Gui(pos, size, style, enabled)
{
	text.setFont(*font);
	text.setString(str);
	text.setCharacterSize(chSize * 4 / 3);
	text.setFillColor(style.textColor);
	
	sf::FloatRect textGlobalBounds = text.getGlobalBounds();
	float w = textGlobalBounds.left + textGlobalBounds.width,
		h = textGlobalBounds.top + textGlobalBounds.height;
	sf::Vector2f newPos(pos.x + size.x / 2 - w / 2,
		pos.y + size.y / 2 - h / 2);
	text.setPosition(newPos);
}

void GuiText::ProcessEvent(const sf::Event&) {}

void GuiText::Update(float deltaTime) {}

void GuiText::Render(sf::RenderWindow *window)
{
	window->draw(text);
}