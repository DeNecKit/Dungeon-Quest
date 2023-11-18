#pragma once

#include "Scene.h"

class SceneManager
{
public:
	static void Init();
	static void ProccessEvent(const sf::Event &);
	static void Update(float);
	static void RenderGUI(sf::RenderWindow*);
	static void RenderSFML(sf::RenderWindow*);
	static void Shutdown();

private:
	static inline Scene *m_currentScene;
};