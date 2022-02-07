#pragma once

#include "Application.hpp"

Application Application::s_Instance;

void Application::Run()
{
    float dt = m_GameClock.getElapsedTime().asSeconds();
    m_GameClock.restart();

	while (m_Window.isOpen())
	{
		m_Window.clear();

		m_Level.Update(dt);
		m_Level.Draw(&m_Window);

		m_Window.display();
	}
}

sf::Vector2i Application::MousePosition()
{
	return sf::Mouse::getPosition(m_Window);
}

Application& Application::Get()
{
	return s_Instance;
}

