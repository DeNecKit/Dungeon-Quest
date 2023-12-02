#include "GuiText.h"
#include "../GameManager.h"

GuiText::GuiText(sf::FloatRect dims, const sf::String& str,
	sf::Font* font, unsigned int chSize, sf::Color textColor,
	sf::Color shadowColor) : Gui(dims),
	textColor(textColor), shadowColor(shadowColor)
{
	text.setFont(*font);
	text.setString(str);
	text.setCharacterSize((int)(chSize * 4 / 3 * GameManager::ResCoefX()));
	text.setFillColor(textColor);
	
	sf::FloatRect textGlobalBounds = text.getGlobalBounds();
	float w = textGlobalBounds.left + textGlobalBounds.width,
		h = textGlobalBounds.top + textGlobalBounds.height;
	innerDimensions = sf::FloatRect(
		dimensions.left + dimensions.width / 2 - w / 2,
		dimensions.top + dimensions.height / 2 - h / 2,
		dimensions.width, dimensions.height);
	text.setPosition(innerDimensions.getPosition());
}

void GuiText::ProcessEvent(const sf::Event&) {}

void GuiText::Update(sf::Time deltaTime) {}

void GuiText::Render(sf::RenderWindow *window)
{
	if (shadowColor != sf::Color::Transparent)
	{
		text.setPosition(
			innerDimensions.left + 2 * GameManager::ResCoefX(),
			innerDimensions.top + 2 * GameManager::ResCoefY());
		text.setFillColor(shadowColor);
		window->draw(text);
		text.setPosition(innerDimensions.getPosition());
		text.setFillColor(textColor);
	}
	window->draw(text);
}