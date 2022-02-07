#pragma once

#include "Bullet.hpp"
#include "Application.hpp"
#include <iostream>

Bullet::Bullet(sf::Vector2f Position, sf::Vector2f Direction)
{
	this->Direction = Direction / (float)sqrt(Direction.x * Direction.x + Direction.y * Direction.y);
	setFillColor(sf::Color::Red);
	setPosition(Position);
	setRotation((atan2(this->Direction.y, this->Direction.x)) * 180.0f / 3.14159265f);
	setSize(sf::Vector2f(10.0f, 10.0f));
	setOrigin(sf::Vector2f(getSize().x / 2, getSize().y / 2));
}

void Bullet::Update(float dt)
{
	m_LifeTime += dt;
	if (m_LifeTime > m_DeathTime)
	{
		Application::Get().CurLevel().Remove(this);
	}
	setFillColor(sf::Color(255, (uint8_t)(255 * (m_LifeTime / m_DeathTime)), 0, 255));
	setPosition(Direction * m_Speed * dt + getPosition());
}