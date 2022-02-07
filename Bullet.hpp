#pragma once

#include "GameObject.hpp"

class Bullet : public GameObject
{
private:
	float m_Speed = 400.0f;
	float m_LifeTime = 0, m_DeathTime = 3;
	sf::Vector2f Direction;
public:
	Bullet(sf::Vector2f Position, sf::Vector2f Direction);
	void Update(float dt) override;
};