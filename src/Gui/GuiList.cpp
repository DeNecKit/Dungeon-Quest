#include "GuiList.h"

GuiList::GuiList(sf::FloatRect dims,
	sf::Color fillColor, sf::Color outlineColor)
	: Gui(dims), rect(dims, fillColor, outlineColor) {}

GuiList::~GuiList()
{
	for (Gui *element : children)
		delete element;
}

void GuiList::ProcessEvent(const sf::Event &event)
{
	for (Gui *element : children)
		element->ProcessEvent(event);
}

void GuiList::Update(sf::Time deltaTime)
{
	for (Gui *element : children)
		element->Update(deltaTime);
}

void GuiList::Render(sf::RenderWindow *window)
{
	rect.Render(window);
	for (Gui *element : children)
		element->Render(window);
}

void GuiList::Append(Gui *element)
{
	children.push_back(element);
}

std::vector<Gui*> GuiList::GetChildren()
{
	return children;
}