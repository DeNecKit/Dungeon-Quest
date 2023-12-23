#pragma once

#include "Scene.h"
#include "../Gui/GuiText.h"
#include "../Gui/GuiButton.h"

class SceneWin final : public Scene
{
public:
	SceneWin();
	~SceneWin();
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void RenderGUI(sf::RenderWindow*) override;
	void RenderSFML(sf::RenderWindow*) override;

private:
	GuiText *text1, *text2;
	GuiButton *back;
};