#include "GuiButton.h"
#include "GameManager.h"

GuiButton::GuiButton(GuiStyle style, const char* text,
	void (*onClick)(const sf::Event&),
	void (*onHover)(const sf::Event&), bool enabled)
	: Gui(style, enabled),
	  OnClick(onClick), OnHover(onHover), isHovered(false)
{
	rect = new sf::RectangleShape(style.size);
	rect->setPosition(style.size);
	rect->setFillColor(style.backgroundColor);
	rect->setOutlineColor(style.outlineColor);
	rect->setOutlineThickness(style.outlineThickness);
	// TODO: text, font
}

void GuiButton::ProcessEvent(const sf::Event &event) {}

void GuiButton::Update() {}

void GuiButton::Render()
{
	sf::RenderWindow *window = GameManager::GetWindow();
	window->draw(*rect);
}