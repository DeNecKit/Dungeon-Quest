#pragma once

#include "SceneManager.h"

class GameManager
{
public:
	static void Init();
	static sf::RenderWindow* GetWindow();
	static unsigned int WindowWidth();
	static unsigned int WindowHeight();
	static float ResCoefX();
	static float ResCoefY();
	static bool IsRunning();
	static void Update();
	static void Close();
	static void Shutdown();

	static bool IsMouseOver(sf::FloatRect rect);

private:
	static inline sf::RenderWindow *window;
	static inline bool isWindowClosed;
	static inline sf::Clock deltaClock;
};