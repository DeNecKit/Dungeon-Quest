#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Level
{
public:
	Level(const sf::String &backLayerTexturePath);
	void ProcessEvent(const sf::Event&);
	void Update(sf::Time deltaTime);
	void RenderGUI(sf::RenderWindow*);
	void RenderSFML(sf::RenderWindow*);

	static Level Level1();

private:
	sf::Texture backLayerTexture;
	sf::Sprite backLayerSprite;
	Player player;
};