#pragma once

#include "GuiRect.h"
#include "GuiText.h"
#include "GuiClickable.h"
#include "../ResourceManager.h"

class GuiButton final : public Gui
{
public:
	GuiButton(sf::FloatRect dims, const sf::String &str,
		unsigned int chSize, void (*onClick)(const sf::Event&),
		sf::Color fillColor = ButtonFillColor,
		sf::Color outlineColor = ButtonOutlineColor,
		sf::Font *font = ResourceManager::GetMainFont());
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;
	void SetEnabled(bool);

private:
	GuiRect rect;
	GuiText text;
	GuiClickable click;
	bool enabled;
	sf::RectangleShape disabledRect;
};