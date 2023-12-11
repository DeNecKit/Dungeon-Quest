#pragma once

#include "Gui.h"
#include "../ResourceManager.h"

class GuiText final : public Gui
{
public:
	GuiText(sf::FloatRect dims, const sf::String &str, unsigned int chSize,
		sf::Font *font = ResourceManager::GetMainFont(),
		sf::Color textColor = Gui::TextColor,
		sf::Color shadowColor = Gui::ShadowColor);
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;
	void SetString(const sf::String &str);

private:
	sf::FloatRect innerDimensions;
	sf::Text text;
	sf::Color textColor, shadowColor;
};