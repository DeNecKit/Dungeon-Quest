#include "GuiButton.h"
#include "GameManager.h"

GuiButton::GuiButton(sf::FloatRect dims, const sf::String &str,
	sf::Font *font, unsigned int chSize,
	void (*onClick)(const sf::Event&),
	sf::Color fillColor, sf::Color textColor,
	sf::Color outlineColor, sf::Color shadowColor)
	: GuiText(dims, str, font, chSize, textColor, shadowColor),
	  OnClick(onClick), isHovered(false)
{
	rect = sf::RectangleShape(dimensions.getSize());
	rect.setPosition(dimensions.getPosition());
	rect.setFillColor(fillColor);
	rect.setOutlineThickness(4.f);
	rect.setOutlineColor(outlineColor);

	hoverRect = sf::RectangleShape(dimensions.getSize());
	hoverRect.setPosition(dimensions.getPosition());
	hoverRect.setFillColor(sf::Color(255, 255, 255, 100));
}

void GuiButton::ProcessEvent(const sf::Event &event)
{
	isHovered = IsMouseOver();
	if (isHovered && event.type == sf::Event::MouseButtonPressed)
		OnClick(event);
}

void GuiButton::Update(sf::Time deltaTime) {}

void GuiButton::Render(sf::RenderWindow *window)
{
	window->draw(rect);
	GuiText::Render(window);
	if (isHovered)
		window->draw(hoverRect);
}