#pragma once

#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "GameObject.hpp"
#include <iostream>

Level::Level()
{
	m_Objects.Add(Player(60.0f));
}

void Level::Remove(GameObject* Object)
{
	m_PendingRemoveObjects.push_back(Object);
}
void Level::Update(float dt)
{
    std::vector<int> ints;

    for(GameObject &Object: m_Objects)
        Object.Update(dt);

    for(const GameObject &Object: m_PendingAddObjects)
	    m_Objects.Add(Object);
	m_PendingAddObjects.Clear();

	for (GameObject* Object : m_PendingRemoveObjects)
        m_Objects.Remove(Object);
	m_PendingRemoveObjects.clear();
}
void Level::Draw(sf::RenderWindow *window)
{
	for(GameObject &Object: m_Objects)
	{
		window->draw(Object);
	}
}