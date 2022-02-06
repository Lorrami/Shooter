#pragma once

#include <SFML/Graphics.hpp>

class GameObject: public sf::RectangleShape
{
public:
	virtual void Update(float dt) = 0;
};