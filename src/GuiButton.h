#pragma once

#include "Gui.h"

class GuiButton : public Gui
{
public:
	GuiButton(GuiStyle style, const char *text,
		void (*onClick)(const sf::Event&),
		void (*onHover)(const sf::Event&), bool enabled = true);
	void ProcessEvent(const sf::Event&) override;
	void Update() override;
	void Render() override;
private:
	sf::RectangleShape *rect;
	sf::Text *text;
	void (*OnClick)(const sf::Event&);
	void (*OnHover)(const sf::Event&);
	bool isHovered;
};