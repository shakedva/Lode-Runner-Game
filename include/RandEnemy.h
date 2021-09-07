//----------------------------------include section---------------------------------
#pragma once
#include "Enemy.h"
//-------------------------------class implementation------------------------------
class RandEnemy : public Enemy
{
public:
	RandEnemy(int, int, int);
	//virtual function
	virtual void move(const sf::Time&)override;
private:
	// m_timer will be a second between 0 - 1 and it will represent when the random enemy will randomize its 
	//direction
	sf::Time m_timer = sf::seconds(INIT);
};