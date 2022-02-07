#pragma once

#include "Player.hpp"
#include "Application.hpp"
#include "Bullet.hpp"

void Player::KeyboardUpdate(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Movement(m_Speed * dt, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Movement(-m_Speed * dt, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Movement(0, m_Speed * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Movement(0, -m_Speed * dt);
	}
}
void Player::RotationUpdate()
{
	float dx = -Application::Get().MousePosition().x + getPosition().x;
	float dy = -Application::Get().MousePosition().y + getPosition().y;
	float rotation = (atan2(dy, dx)) * 180.0f / 3.14159265f;
	setRotation(rotation);
}
void Player::Movement(float dx, float dy)
{
	setPosition(getPosition() + sf::Vector2f(dx, dy));
}
void Player::Shooting()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		float dx = Application::Get().MousePosition().x - getPosition().x;
		float dy = Application::Get().MousePosition().y - getPosition().y;
		Application::Get().CurLevel().Add(new Bullet(getPosition(), sf::Vector2f(dx, dy)));
	}
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
	KeyboardUpdate(dt);
	RotationUpdate();
	Shooting();
}