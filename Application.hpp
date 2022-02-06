#pragma once

#include <SFML/Graphics.hpp>
#include "Level.hpp"

class Application
{
	static Application s_Instance;
private:
	sf::RenderWindow m_Window{ sf::VideoMode(700, 700), "Test"};
	Level m_Level;
private:
	Application() = default;
public:
	void Run();
	sf::Vector2i MousePosition();

	static Application &Get();
};