#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "GameObject.hpp"
#include <iostream>

Level::Level()
{
	m_Objects.push_back(new Player(60.0f));
}
void Level::Add(GameObject* Object)
{
	m_PendingAddObjects.push_back(Object);
}
void Level::Remove(GameObject* Object)
{
	m_PendingRemoveObjects.push_back(Object);
}
void Level::Update(float dt)
{
    	for(GameObject *Object: m_Objects)
        	Object->Update(dt);

	m_Objects.insert(m_Objects.end(), m_PendingAddObjects.begin(), m_PendingAddObjects.end());
	m_PendingAddObjects.clear();

	for (GameObject* ObjectToRemove : m_PendingRemoveObjects)
	{ 
		for (int i = 0; i < m_Objects.size(); i++)
		{
			if (ObjectToRemove == m_Objects[i])
			{
				delete m_Objects[i];
				std::swap(m_Objects[i], m_Objects.back());
				m_Objects.pop_back();
			}
		}
	}
	m_PendingRemoveObjects.clear();
}
void Level::Draw(sf::RenderWindow *window)
{
	for(GameObject *Object: m_Objects)
	{
		window->draw(*Object);
	}
}
