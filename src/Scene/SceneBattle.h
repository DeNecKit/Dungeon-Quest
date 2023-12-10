#pragma once

#include "Scene.h"

class SceneBattle final : public Scene
{
public:
	SceneBattle();
	void ProcessEvent(const sf::Event&) override;
	void Update(sf::Time deltaTime) override;
	void RenderGUI(sf::RenderWindow*) override;
	void RenderSFML(sf::RenderWindow*) override;

private:

};