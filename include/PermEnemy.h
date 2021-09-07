//----------------------------------include section---------------------------------
#pragma once
#include "Enemy.h"

//---------------------------------class implementation-----------------------------
class PermEnemy : public Enemy
{
public:
	PermEnemy(int, int, int);
	virtual void move(const sf::Time&)override;
};