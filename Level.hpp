#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"

class Level
{
	static Level l_Instance;
public:
	std::vector<GameObject*> m_Objects;
public:
	Level();
	void Add(GameObject* Object);
	void Update(float dt);
	void Draw(sf::RenderWindow *window);

	static Level& Get();
};