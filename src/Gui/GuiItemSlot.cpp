#include "GuiItemSlot.h"

GuiItemSlot::GuiItemSlot(sf::FloatRect dims,
	sf::Color fillColor, sf::Color textColor, Item* item,
	sf::Color outlineColor, sf::Color shadowColor)
	: Gui(dims), item(item),
	rect(dims, fillColor, outlineColor),
	click(dims, [](const sf::Event&) {}) {}

void GuiItemSlot::ProcessEvent(const sf::Event &event)
{
	click.ProcessEvent(event);
}

void GuiItemSlot::Update(sf::Time deltaTime)
{
}

void GuiItemSlot::Render(sf::RenderWindow *window)
{
	rect.Render(window);
	click.Render(window);
	if (item != nullptr)
	{
		sf::Sprite s = item->GetSprite();
		int spSize = (int)ItemTemplate::GetSize();
		s.setPosition(
			dimensions.left + dimensions.width/2.f - spSize/2.f,
			dimensions.top + dimensions.height/2.f - spSize/2.f);
		window->draw(s);
	}
}