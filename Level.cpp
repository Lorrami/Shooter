#pragma once

#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "GameObject.hpp"

Level::Level()
{
	m_Objects.push_back(new Player(60.0f));
}
void Level::Update()
{
	dt = clock.getElapsedTime().asSeconds();
	clock.restart();
}
void Level::Draw(sf::RenderWindow *window)
{
	for(GameObject *Object: m_Objects)
	{
		Object->Update(dt);
		window->draw(*Object);
	}
}