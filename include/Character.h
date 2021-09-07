//----------------------------------include section---------------------------------
#pragma once
#include "GameObjects.h"
//---------------------------------class implementation-----------------------------
class Character : public GameObjects
{
public:
	using GameObjects::GameObjects;

	virtual void move(const sf::Time& deltaTime)=0;
	void moveToDefaultLocation();

protected:
	void hitAwall(WallFloor& gameObject);
	
	sf::Vector2f m_direction, // the direction of the character
		m_defaultLocation; // the default direction of the character

};