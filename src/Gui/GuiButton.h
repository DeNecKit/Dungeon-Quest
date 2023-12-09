#pragma once

#include "GuiRect.h"
#include "GuiText.h"
#include "GuiClickable.h"

class GuiButton final : public Gui
{
public:
	GuiButton(sf::FloatRect dims, const sf::String &str,
		sf::Font *font, unsigned int chSize,
		void (*onClick)(const sf::Event&));
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;

private:
	GuiRect rect;
	GuiText text;
	GuiClickable click;
};