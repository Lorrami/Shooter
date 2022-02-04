#pragma once

#include <SFML/Graphics.hpp>
#include "Level.hpp"

class Application
{
private:
	sf::RenderWindow m_Window{ sf::VideoMode(700, 700), "Test"};
	Level m_Level;
public:
	void Run();
};