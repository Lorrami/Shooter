#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"

class Level
{
private:
	std::vector<GameObject*> m_Objects;
	std::vector<GameObject*> m_PendingAddObjects;
	std::vector<GameObject*> m_PendingRemoveObjects;
public:
	Level();
	void Add(GameObject* Object);
	void Remove(GameObject* Object);
	void Update(float dt);
	void Draw(sf::RenderWindow *window);
};