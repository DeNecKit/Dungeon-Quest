#pragma once

#include "Scene.h"
#include "Level.h"
#include "GuiText.h"

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

private:
	Level *level;
	GuiText *interText;
	bool isInterTextVisible;

	static inline SceneGame *instance;
};