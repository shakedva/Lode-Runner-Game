//----------------------------------include section---------------------------------
#pragma once
#include "Enemy.h"

//---------------------------------class implementation-----------------------------
class SmartEnemy : public Enemy
{
public:
	SmartEnemy(int, int, int, const Player&); // ctor
	virtual void move(const sf::Time& )override;
private:
	const Player& m_p; // receives the player so it will know its location
};