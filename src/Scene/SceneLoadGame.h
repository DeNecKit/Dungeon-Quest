#pragma once

#include "Scene.h"
#include "../Gui/GuiText.h"
#include "../Gui/GuiButton.h"
#include "../Gui/GuiList.h"

class SceneLoadGame final : public Scene
{
public:
	SceneLoadGame();
	~SceneLoadGame();
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void RenderGUI(sf::RenderWindow*) override;
	void RenderSFML(sf::RenderWindow*) override;

private:
	GuiText *text;
	GuiList *saves;
	GuiButton *back;
};