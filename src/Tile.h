#pragma once

#include "Animatable.h"
#include <SFML/Graphics.hpp>

class Tile : public Animatable
{
public:
	Tile(unsigned int id, sf::Vector2u pos);
	virtual bool IsWall();
	virtual void ProcessEvent(const sf::Event&);
	virtual void Update(sf::Time deltaTime);
	virtual void Render(sf::RenderWindow*);
	unsigned int GetId();
	sf::Vector2f GetPos();

protected:
	unsigned int id;
	sf::Vector2f position;
};