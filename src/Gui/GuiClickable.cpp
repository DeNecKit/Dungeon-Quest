#include "GuiClickable.h"

GuiClickable::GuiClickable(sf::FloatRect dims,
	void (*onClick)(const sf::Event&), bool doHover, GuiDraggable *drag)
	: Gui(dims), OnClick(onClick), isPressed(false),
	doHover(doHover), isHovered(false), drag(drag), dragReleased(false)
{
	hoverRect = sf::RectangleShape(dimensions.getSize());
	hoverRect.setPosition(dimensions.getPosition());
	hoverRect.setFillColor(sf::Color(255, 255, 255, 100));
}

GuiClickable::~GuiClickable()
{
	if (drag != nullptr) delete drag;
}

void GuiClickable::ProcessEvent(const sf::Event &event)
{
	isHovered = IsMouseOver();
	if (isHovered) isPressed = isPressed ||
		event.type == sf::Event::MouseButtonPressed;
	if (event.type == sf::Event::MouseButtonReleased)
	{
		isPressed = false;
		if (!ShouldDrag() && isHovered) OnClick(event);
		if (ShouldDrag())
		{
			drag->Reset();
			dragReleased = true;
		}
	}
}

void GuiClickable::Update(sf::Time deltaTime)
{
	if (drag != nullptr && isHovered && isPressed)
		drag->Update(deltaTime);
}

void GuiClickable::Render(sf::RenderWindow *window)
{
	if (doHover && isHovered) window->draw(hoverRect);
	dragReleased = false;
}

bool GuiClickable::IsPressed()
{
	return isPressed;
}

bool GuiClickable::IsHovered()
{
	return isHovered;
}

bool GuiClickable::ShouldDrag()
{
	return drag != nullptr && drag->ShouldDrag();
}

bool GuiClickable::DragReleased()
{
	return dragReleased;
}