#pragma once

#include "Scene.h"
#include "../Level.h"
#include "../Gui/GuiText.h"
#include "../Gui/GuiList.h"

class SceneGame final : public Scene
{
public:
	SceneGame();
	~SceneGame();
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time) override;
	void RenderGUI(sf::RenderWindow*) override;
	void RenderSFML(sf::RenderWindow*) override;

	static void InteractionNotify();
	static void SetPause(bool pause);

private:
	Level *level;
	GuiText *interText;
	GuiList *pauseMenu;
	bool isInterTextVisible, isPaused;

	static inline SceneGame *instance;
};