//----------------------------------include section---------------------------------
#include "SmartEnemy.h"

// Smart enemy constructor 
SmartEnemy::SmartEnemy(int row, int col, int index, const Player& p)
	: Enemy(row, col, index), m_p(p)
{
	m_direction = sf::Vector2f(-1, 0); // its first direction is to the left
	m_defaultLocation = sf::Vector2f((float)col * TILE_SIZE, (float)row * TILE_SIZE);
}
// smart enemy moves to the col of the player
void SmartEnemy::move(const sf::Time& deltaTime)
{
	if (!m_inPit) // if the enemy is not in a pit
	{
		// if the player is going to the left - turn left
		if (m_p.getLocation().x < m_objSprite.getPosition().x)
			m_direction = sf::Vector2f(-1, 0);
		// if the player is going to the right - turn right
		else
			m_direction = sf::Vector2f(1, 0);

		m_objSprite.move(m_direction * enemy_speed * deltaTime.asSeconds());
	}
}