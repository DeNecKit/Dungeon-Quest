#pragma once

#include "GuiStyle.h"
#include <SFML/Graphics.hpp>

class Gui
{
public:
	Gui(GuiStyle style, bool enabled = true);
	virtual ~Gui();
	virtual void ProcessEvent(const sf::Event &) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	bool IsMouseOver();

private:
	bool isEnabled, needsRefresh;
	GuiStyle style;
};