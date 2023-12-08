#pragma once

#include <SFML/Graphics.hpp>
#include "Gui.h"
#include "GuiDraggable.h"

class GuiClickable final : public Gui
{
public:
	GuiClickable(sf::FloatRect dims,
		void (*onClick)(const sf::Event&),
		bool doHover = true, GuiDraggable *drag = nullptr);
	~GuiClickable();
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;
	bool IsPressed();
	bool IsHovered();
	bool ShouldDrag();
	bool DragReleased();

private:
	void (*OnClick)(const sf::Event&);
	bool isPressed, doHover, isHovered;
	sf::RectangleShape hoverRect;
	GuiDraggable *drag;
	bool dragReleased;
};