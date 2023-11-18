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
	
	text.setPosition(pos);
	text.setFont(*font);
	text.setString(str);
	text.setCharacterSize(chSize * 4 / 3);
	text.setFillColor(style.textColor);
}

void GuiButton::ProcessEvent(const sf::Event &event)
{
	if (IsMouseOver() && OnHover != nullptr)
		OnHover(event);
	if (IsMouseOver() && event.type == sf::Event::MouseButtonPressed)
		OnClick(event);
}

void GuiButton::Update(float deltaTime) {}

void GuiButton::Render(sf::RenderWindow *window)
{
	window->draw(rect);
	window->draw(text);
}