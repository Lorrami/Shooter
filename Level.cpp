#pragma once

#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "GameObject.hpp"

Level::Level()
{
	m_Objects.push_back(new Player(60.0f));
}
void Level::Update(float dt)
{
    for(GameObject *Object: m_Objects)
        Object->Update(dt);
}
void Level::Draw(sf::RenderWindow *window)
{
	for(GameObject *Object: m_Objects)
	{
		window->draw(*Object);
	}
}