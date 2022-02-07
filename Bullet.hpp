#pragma once

#include "GameObject.hpp"

class Bullet : public GameObject
{
private:

public:
	Bullet(sf::Vector2f Position);
	void Update(float dt) override;
};