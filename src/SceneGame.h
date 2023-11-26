#pragma once

#include "Scene.h"
#include "Level.h"

class SceneGame final : public Scene
{
public:
	SceneGame();
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time) override;
	void RenderGUI(sf::RenderWindow*) override;
	void RenderSFML(sf::RenderWindow*) override;
private:
	Level level;
};