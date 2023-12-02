#pragma once

#include "GuiRect.h"
#include "GuiText.h"

class GuiButton final : public Gui
{
public:
	GuiButton(sf::FloatRect dims, const sf::String &str,
		sf::Font *font, unsigned int chSize,
		void (*onClick)(const sf::Event&),
		sf::Color fillColor, sf::Color textColor,
		sf::Color outlineColor = sf::Color::Transparent,
		sf::Color shadowColor = sf::Color::Transparent);
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;

private:
	GuiRect rect;
	GuiText text;
	sf::RectangleShape hoverRect;
	void (*OnClick)(const sf::Event&);
	bool isHovered;
};