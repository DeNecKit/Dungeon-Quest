#pragma once

#include "Scene.h"
#include "../Gui/GuiProgressBar.h"
#include "../Gui/GuiList.h"
#include <vector>

class SceneBattle final : public Scene
{
public:
	SceneBattle();
	~SceneBattle();
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void RenderGUI(sf::RenderWindow*) override;
	void RenderSFML(sf::RenderWindow*) override;

private:
	GuiProgressBar *playerHealthBar;
	std::vector<GuiProgressBar*> enemiesHealthBar;
	GuiList *actionsMenu, *pauseMenu, *inventoryGui;
};