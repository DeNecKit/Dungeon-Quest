#pragma once

#include "SceneManager.h"

class GameManager
{
public:
	static void Init();
	static sf::RenderWindow* GetWindow();
	static unsigned int WindowWidth();
	static unsigned int WindowHeight();
	static bool IsRunning();
	static void Update();
	static void Close();
	static void Shutdown();

private:
	static inline sf::RenderWindow *m_window;
	static inline bool m_isWindowClosed;
	static inline sf::Clock m_deltaClock;
};