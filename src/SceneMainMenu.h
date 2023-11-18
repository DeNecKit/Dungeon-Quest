#pragma once

#include "Scene.h"
#include "GuiButton.h"
#include "GuiText.h"

class SceneMainMenu final : public Scene
{
public:
	SceneMainMenu();
	~SceneMainMenu();
	void ProcessEvent(const sf::Event&) override;
	void Update(float) override;
	void RenderGUI(sf::RenderWindow*) override;
	void RenderSFML(sf::RenderWindow*) override;
private:
	GuiButton *btnNewGame, *btnLoadGame, *btnExit;
	GuiText *title;
	sf::Font* font_tmp;
};