#pragma once

#include <SFML/Graphics.hpp>
#include "Level.hpp"

class Application
{
	static Application s_Instance;
private:
	sf::RenderWindow m_Window{ sf::VideoMode(700, 700), "Shooter"};
	Level m_Level;
    sf::Clock m_GameClock;
private:
	Application() = default;
public:
	void Run();
	sf::Vector2i MousePosition();
	Level& CurLevel();

	static Application &Get();
};