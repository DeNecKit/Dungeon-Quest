#pragma once

#include <SFML/Graphics.hpp>

class GameManager
{
public:
	static void Init(sf::RenderWindow &window)
	{
		m_window = &window;
	}

	static sf::RenderWindow* GetWindow()
	{
		return m_window;
	}

	static void CloseWindow()
	{
		if (m_isWindowClosed) return;
		m_window->close();
		m_isWindowClosed = true;
	}

private:
	static inline sf::RenderWindow *m_window;
	static inline bool m_isWindowClosed;
};