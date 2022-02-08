#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "PolymorphList.hpp"

class Level
{
private:
	PolymorphList<GameObject> m_Objects;
	PolymorphList<GameObject> m_PendingAddObjects;
	std::vector<GameObject*> m_PendingRemoveObjects;
public:
	Level();

    template<class GameObjectType>
	void Add(GameObjectType Object){
        m_PendingAddObjects.Add(Object);
    }

	void Remove(GameObject* Object);
	void Update(float dt);
	void Draw(sf::RenderWindow *window);
};