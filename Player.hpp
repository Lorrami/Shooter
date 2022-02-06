#pragma once

#include "GameObject.hpp"

class Player : public GameObject
{
private:
	float m_Speed = 200.0f;
	void m_Movement(float dx, float dy);
public:
	Player(float m_Size);
	void Update(float dt) override;
};