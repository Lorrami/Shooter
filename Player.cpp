#include "Player.hpp"

void Player::m_Movement(float dx, float dy)
{
	setPosition(getPosition() + sf::Vector2f(dx, dy));
}

Player::Player(float m_Size)
{
	setSize(sf::Vector2f(m_Size, m_Size));
	setPosition(sf::Vector2f(60.0f, 60.0f));
	setFillColor(sf::Color::Red);
}
void Player::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_Movement(m_Speed * dt, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_Movement(-m_Speed * dt, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_Movement(0, m_Speed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_Movement(0, -m_Speed * dt);
	}
}
