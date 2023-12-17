#include "GuiText.h"
#include "../GameManager.h"

sf::FloatRect centerText(sf::FloatRect dims, const sf::Text &text)
{
	sf::FloatRect textLocalBounds = text.getLocalBounds();
	float w = textLocalBounds.left + textLocalBounds.width,
		h = textLocalBounds.top + textLocalBounds.height;
	return sf::FloatRect(
		dims.left + dims.width / 2 - w / 2,
		dims.top + dims.height / 2 - h / 2,
		dims.width, dims.height);
}

GuiText::GuiText(sf::FloatRect dims, const sf::String &str,
	unsigned int chSize, bool alignCenter, sf::Font *font,
	sf::Color textColor, sf::Color shadowColor) : Gui(dims),
	textColor(textColor), shadowColor(shadowColor), alignCenter(alignCenter)
{
	text.setFont(*font);
	text.setString(str);
	text.setCharacterSize((int)(chSize * 4 / 3 * GameManager::ResCoefX()));
	text.setFillColor(textColor);
	innerDimensions = alignCenter ? centerText(dimensions, text) : dimensions;
	text.setPosition(innerDimensions.getPosition());
	innerDimensions = sf::FloatRect(innerDimensions.getPosition(),
		text.getLocalBounds().getSize() + text.getLocalBounds().getPosition());
	dimensions = innerDimensions;
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

void GuiText::SetString(const sf::String &str)
{
	text.setString(str);
	if (alignCenter) innerDimensions = centerText(dimensions, text);
	text.setPosition(innerDimensions.getPosition());
}

void GuiText::SetDimensions(sf::FloatRect dims)
{
	dimensions = dims;
	innerDimensions = alignCenter ? centerText(dims, text) : dims;
}

void GuiText::Stretch()
{
	dimensions = sf::FloatRect(dimensions.getPosition(),
		text.getLocalBounds().getSize() + text.getLocalBounds().getPosition());
}