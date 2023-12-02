#pragma once

#include "Scene.h"
#include "../Gui/GuiButton.h"
#include "../Gui/GuiText.h"

class SceneMainMenu final : public Scene
{
public:
	SceneMainMenu();
	~SceneMainMenu();
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time) override;
	void RenderGUI(sf::RenderWindow*) override;
	void RenderSFML(sf::RenderWindow*) override;
private:
	GuiButton *btnNewGame, *btnLoadGame, *btnExit;
	GuiText *title;
};