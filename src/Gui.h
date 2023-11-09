#pragma once

#include <SFML/Graphics.hpp>

class GuiStyle
{
public:
	unsigned int posX, posY, sizeX, sizeY;
	sf::Color backgroundColor, outlineColor, textColor;
	float outlineThickness;

	GuiStyle(unsigned int posX, unsigned int posY,
		unsigned int sizeX, unsigned int sizeY,
		sf::Color backgroundColor, sf::Color outlineColor,
		sf::Color textColor, float outlineThickness);
};

class Gui
{
public:
	Gui(GuiStyle style, bool enabled);

	virtual void ProcessEvent(const sf::Event &) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

private:
	bool isEnabled, needsRefresh;
	GuiStyle style;
};

class GuiClickable : public Gui
{
	GuiClickable(GuiStyle style, bool enabled);

	virtual void OnClick(const sf::Event&) = 0;

	virtual void ProcessEvent(const sf::Event &) override;
};

class GuiButton : public Gui
{
public:
	GuiButton(GuiStyle style, bool enabled);

};