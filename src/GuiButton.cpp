#include "GuiButton.h"
#include "GameManager.h"

GuiButton::GuiButton(sf::Vector2f pos, sf::Vector2f size,
	GuiStyle style, const sf::String &str,
	sf::Font* font, unsigned int chSize,
	void (*onClick)(const sf::Event&),
	void (*onHover)(const sf::Event&), bool enabled)
	: Gui(pos, size, style, enabled),
	  OnClick(onClick), OnHover(onHover), isHovered(false)
{
	rect = sf::RectangleShape(size);
	rect.setPosition(pos);
	rect.setFillColor(style.backgroundColor);
	rect.setOutlineColor(style.outlineColor);
	rect.setOutlineThickness(style.outlineThickness);

	hoverRect = sf::RectangleShape(size);
	hoverRect.setPosition(pos);
	hoverRect.setFillColor(sf::Color(255, 255, 255, 100));
	
	text.setFont(*font);
	text.setString(str);
	text.setCharacterSize(chSize * 4 / 3);
	text.setFillColor(style.textColor);

	sf::FloatRect textGlobalBounds = text.getGlobalBounds();
	float w = textGlobalBounds.left + textGlobalBounds.width,
		h = textGlobalBounds.top + textGlobalBounds.height;
	sf::Vector2f textPos(pos.x + size.x / 2 - w / 2,
		pos.y + size.y / 2 - h / 2);
	text.setPosition(textPos);
}

void GuiButton::ProcessEvent(const sf::Event &event)
{
	isHovered = IsMouseOver();
	if (isHovered && OnHover != nullptr)
		OnHover(event);
	if (IsMouseOver() && event.type == sf::Event::MouseButtonPressed)
		OnClick(event);
}

void GuiButton::Update(sf::Time deltaTime) {}

void GuiButton::Render(sf::RenderWindow *window)
{
	window->draw(rect);
	window->draw(text);
	if (isHovered)
		window->draw(hoverRect);
}