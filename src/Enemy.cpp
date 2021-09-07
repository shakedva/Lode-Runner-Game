//----------------------------------include section---------------------------------
#include "Enemy.h"
#include "Pit.h"


//----------------------------------functions section---------------------------------
//when there is a collision with a game object, we double dispach
void Enemy::handleCollision(GameObjects& gameObject)
{
	if (&gameObject == this)
		return;
	//double dispatch
	gameObject.handleCollision(*this);
}

// enemy collides with player
void  Enemy::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}
// turns the enemy to the opposite direction 
void Enemy::turnTheOtherDirection()
{
	m_direction.x = -m_direction.x;
	m_objSprite.move(m_direction.x,0);
}

sf::Vector2f Enemy::getDirection() const
{
	return m_direction;
}

// this function takes the enemy out of the pit, 40 pixels upward and changes the value of m_inPit
void Enemy::takeOutOfPit()
{
	m_objSprite.move(0, -TILE_SIZE);
	m_direction = sf::Vector2f(-1, 0);
	m_inPit = false;
}
bool Enemy::isInPit() const
{
	return m_inPit;
}
void Enemy::handleCollision(WallFloor& gameObject)
{
	turnTheOtherDirection();
	hitAwall(gameObject);
}
// if the enemy collides with an empty pit, he is falling into it
void Enemy::handleCollision(Pit& gameObject)
{
	if (gameObject.isPitEmpty())
	{
		if (!m_inPit)
		{
			gameObject.setEnemyInPit(this); // the pit receives the enemy inside it
			m_inPit = true;
			m_objSprite.setPosition(gameObject.getPosition().x, m_objSprite.getPosition().y+ TILE_SIZE); // falls to pit
			m_direction = sf::Vector2f(0, 0);
		}
	}
}
