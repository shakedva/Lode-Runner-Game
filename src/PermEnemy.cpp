//----------------------------------include section---------------------------------
#include "PermEnemy.h"

PermEnemy::PermEnemy(int row, int col, int index)
	: Enemy(row, col, index)
{
	m_direction = sf::Vector2f(1, 0); // its first direction is to the right
	m_defaultLocation = sf::Vector2f((float)col * TILE_SIZE, (float)row * TILE_SIZE);
}
// the permanent is going right and left until collides with wall and continue to the other direction 
void PermEnemy::move(const sf::Time& deltaTime)
{
	m_objSprite.move(m_direction * enemy_speed * deltaTime.asSeconds());
}