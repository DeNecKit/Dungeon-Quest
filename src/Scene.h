#pragma once

#include <SFML/Graphics.hpp>

class Scene
{
public:
	virtual ~Scene();
	virtual void ProcessEvent(const sf::Event &) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void RenderGUI(sf::RenderWindow*) = 0;
	virtual void RenderSFML(sf::RenderWindow*) = 0;
};