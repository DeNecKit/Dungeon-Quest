#pragma once

#include <SFML/Graphics.hpp>
class Scene
{
public:
	virtual void ProcessEvent(const sf::Event &) = 0;
	virtual void RenderGUI() = 0;
	virtual void RenderSFML() = 0;
};

class SceneMainMenu final : public Scene
{
public:
	void ProcessEvent(const sf::Event &) override;
	void RenderGUI() override;
	void RenderSFML() override;
};