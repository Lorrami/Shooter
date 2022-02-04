#pragma once

#include "GameObject.hpp"

class Player : public GameObject
{
public:
	Player(float m_Size);
	void Update() override;
};