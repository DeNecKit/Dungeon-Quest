#include "GuiClickable.h"

GuiClickable::GuiClickable(sf::FloatRect dims,
	void (*onClick)(Gui *self), bool doHover,
	GuiDraggable *drag, bool isClickable)
	: Gui(dims), OnClick(onClick), isPressed(false),
	doHover(doHover), isHovered(false), drag(drag),
	dragReleased(false), isClickable(isClickable)
{
	hoverRect = sf::RectangleShape(dimensions.getSize());
	hoverRect.setPosition(dimensions.getPosition());
	hoverRect.setFillColor(sf::Color(255, 255, 255, 100));
	clickRect = sf::RectangleShape(dimensions.getSize());
	clickRect.setPosition(dimensions.getPosition());
	clickRect.setFillColor(sf::Color(0, 0, 0, 100));
}

GuiClickable::~GuiClickable()
{
	if (drag != nullptr) delete drag;
}

void GuiClickable::ProcessEvent(const sf::Event &event)
{
	isHovered = IsMouseOver();
	if (isHovered && isClickable) isPressed = isPressed ||
		event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left;
	else isPressed = false;
	if (ShouldDrag()) isPressed = false;
	if (isClickable && event.type == sf::Event::MouseButtonReleased)
	{
		if (isHovered && isPressed && !ShouldDrag()) OnClick(this);
		if (ShouldDrag())
		{
			drag->Reset();
			dragReleased = true;
		}
		isPressed = false;
	}
}

void GuiClickable::Update(sf::Time deltaTime)
{
	if (isClickable && drag != nullptr && isHovered && isPressed)
		drag->Update(deltaTime);
}

void GuiClickable::Render(sf::RenderWindow *window)
{
	if (doHover && isHovered)
		if (isPressed) window->draw(clickRect);
		else window->draw(hoverRect);
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