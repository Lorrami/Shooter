#pragma once

#include "Player.hpp"
#include "Application.hpp"
#include <iostream>

void Player::m_KeyboardUpdate(float dt)
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
void Player::m_RotationUpdate()
{
	float dx = -Application::Get().MousePosition().x + getPosition().x;
	float dy = -Application::Get().MousePosition().y + getPosition().y;
	float rotation = (atan2(dy, dx)) * 180.0f / 3.14159265f;
	std::cout << rotation << std::endl;
	setRotation(rotation);
}
void Player::m_Movement(float dx, float dy)
{
	setPosition(getPosition() + sf::Vector2f(dx, dy));
}

Player::Player(float m_Size)
{
	setSize(sf::Vector2f(m_Size, m_Size));
	setPosition(sf::Vector2f(60.0f, 60.0f));
	setOrigin(sf::Vector2f(m_Size/2, m_Size/2));
	setFillColor(sf::Color::Red);
}
void Player::Update(float dt)
{
	m_KeyboardUpdate(dt);
	m_RotationUpdate();
}
