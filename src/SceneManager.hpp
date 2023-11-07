#pragma once

#include "Scene.hpp"

class SceneManager
{
public:
	static void Init();
	static void ProccessEvent(const sf::Event &);
	static void RenderGUI();
	static void RenderSFML();
	static void Shutdown();

private:
	static inline Scene *m_currentScene;
};