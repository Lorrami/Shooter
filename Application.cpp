#include "Application.hpp"

void Application::Run()
{
	while (m_Window.isOpen())
	{
		m_Level.Update();
		m_Level.Draw(&m_Window);

		m_Window.display();
	}
}

