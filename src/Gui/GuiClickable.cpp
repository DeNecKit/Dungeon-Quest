#include "GuiClickable.h"

GuiClickable::GuiClickable(sf::FloatRect dims,
	void (*onClick)(const sf::Event&), bool doHover)
	: Gui(dims), OnClick(onClick), isPressed(false),
	doHover(doHover), isHovered(false)
{
	hoverRect = sf::RectangleShape(dimensions.getSize());
	hoverRect.setPosition(dimensions.getPosition());
	hoverRect.setFillColor(sf::Color(255, 255, 255, 100));
}

void GuiClickable::ProcessEvent(const sf::Event &event)
{
	isHovered = IsMouseOver();
	if (!isHovered) return;
	isPressed = isPressed ||
		event.type == sf::Event::MouseButtonPressed;
	if (isPressed && event.type == sf::Event::MouseButtonReleased)
	{
		isPressed = false;
		OnClick(event);
	}
}

void GuiClickable::Update(sf::Time deltaTime) {}

void GuiClickable::Render(sf::RenderWindow *window)
{
	if (doHover && isHovered) window->draw(hoverRect);
}

bool GuiClickable::IsPressed()
{
	return isPressed;
}

bool GuiClickable::IsHovered()
{
	return isHovered;
}