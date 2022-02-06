#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"

class Level
{
private:
	sf::Clock clock;
	std::vector<GameObject*> m_Objects;
public:
	float dt = 0;
	Level();
	void Update();
	void Draw(sf::RenderWindow *window);
};