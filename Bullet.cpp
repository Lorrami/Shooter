#pragma once

#include "Bullet.hpp"

Bullet::Bullet(sf::Vector2f Position)
{
	setFillColor(sf::Color::Red);
	setPosition(Position);
}

void Bullet::Update(float dt)
{

}