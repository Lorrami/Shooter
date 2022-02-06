#include "Player.hpp"

Player::Player(float m_Size)
{
	setSize(sf::Vector2f(m_Size, m_Size));
	setPosition(sf::Vector2f(60.0f, 60.0f));
	setFillColor(sf::Color::Red);
}
void Player::Update()
{
	
}
