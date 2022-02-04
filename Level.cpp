#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include "GameObject.hpp"

void Level::Update()
{
	m_Objects.push_back(new Player(60.0f));
}
void Level::Draw(sf::RenderWindow *window)
{
	for(GameObject *var: m_Objects)
	{
		window->draw(*var);
	}
}