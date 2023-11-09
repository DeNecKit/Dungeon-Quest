#pragma once

#include "Scene.h"

class SceneManager
{
public:
	static void Init();
	static void ProccessEvent(const sf::Event &);
	static void Update(float);
	static void RenderGUI();
	static void RenderSFML();
	static void Shutdown();

private:
	static inline Scene *m_currentScene;
};