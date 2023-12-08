#include "GuiDraggable.h"

GuiDraggable::GuiDraggable(sf::Time holdTime)
	: holdTime(holdTime) {}

void GuiDraggable::Update(sf::Time deltaTime)
{
	if (ShouldDrag()) return;
	passedTime += deltaTime;
}

bool GuiDraggable::ShouldDrag()
{
	return passedTime > holdTime;
}

void GuiDraggable::Reset()
{
	passedTime = sf::Time::Zero;
}