#pragma once

#include "Gui.h"
#include "GuiRect.h"
#include "GuiText.h"
#include "../ResourceManager.h"

class GuiProgressBar final : public Gui
{
public:
	GuiProgressBar(sf::FloatRect dims, sf::Color barClr,
		unsigned int &val, unsigned int &maxVal, unsigned int chSize = 14,
		sf::Font *font = ResourceManager::GetMainFont());
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void Render(sf::RenderWindow*) override;

	static sf::Vector2f GetHealthBarSize();

private:
	unsigned int &value, &maxValue;
	GuiRect background, bar;
	GuiText text;
};