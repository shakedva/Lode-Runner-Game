//----------------------------------include section---------------------------------
#include "Character.h"
#include "WallFloor.h"

// return the character to its default location in the game
void Character::moveToDefaultLocation()
{
	m_objSprite.setPosition(m_defaultLocation);
}
void Character::hitAwall(WallFloor& gameObject)
{
	if (gameObject.getPosition().x > m_objSprite.getPosition().x)  // this is a collision with right wall
		m_objSprite.move(-1, 0);
	if (gameObject.getPosition().x < m_objSprite.getPosition().x)  // this is a collision with left wall
		m_objSprite.move(1, 0);
}