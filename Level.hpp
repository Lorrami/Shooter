#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"

class Level
{
private:
	std::vector<GameObject*> m_Objects;
public:
	void Update();
	void Draw(sf::RenderWindow *window);
};