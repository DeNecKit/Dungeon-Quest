#pragma once

#include "Scene.h"
#include "GuiButton.h"

class SceneMainMenu final : public Scene
{
public:
	SceneMainMenu();
	~SceneMainMenu();
	void ProcessEvent(const sf::Event&) override;
	void Update(float) override;
	void RenderGUI() override;
	void RenderSFML() override;
private:
	GuiButton *btnNewGame, *btnLoadGame, *btnExit;
};