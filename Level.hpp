#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"

class Level
{
private:
	std::vector<GameObject*> m_Objects;
public:
	Level();
	void Update(float dt);
	void Draw(sf::RenderWindow *window);
};