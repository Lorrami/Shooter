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

	for (GameObject* Object : m_PendingRemoveObjects)
	{ 
		for (int i = 0; i < m_Objects.size(); i++)
		{
			if (Object == m_Objects[i])
			{
				GameObject* TimeParam = m_Objects[i];
				m_Objects[i] = m_Objects[m_Objects.size() - 1];
				m_Objects[m_Objects.size() - 1] = TimeParam;
				m_Objects.pop_back();
				delete TimeParam;
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
