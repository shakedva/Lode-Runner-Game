//----------------------------------include section---------------------------------
#include "RandEnemy.h"
#include <time.h>
//-------------------------------functions implementation------------------------------
RandEnemy::RandEnemy(int row, int col, int index)
	: Enemy(row, col, index)
{
	m_direction = sf::Vector2f(-1, 0); //initialize rand enemy to turn left
	//save his default location if user loses the current level
	m_defaultLocation = sf::Vector2f((float)col * TILE_SIZE, (float)row * TILE_SIZE);
}

void RandEnemy::move(const sf::Time& deltaTime)
{
	m_timer += deltaTime; // we add the time passed to the timer
	// if a second passed we randomize a new direction and restart the timer
	if (m_timer.asSeconds() >= 1)
	{
		m_timer = sf::seconds(INIT);

		int typeOfDirection = rand() % 2 + 1; //randomize a number between 1-2
		switch (typeOfDirection)
		{
		case 1: // turn left
			m_direction = sf::Vector2f(-1, 0);
			break;
		case 2: // turn right
			m_direction = sf::Vector2f(1, 0);
			break;
		}
	}
	if (!m_inPit)
	{
		//move the random enemy according to his current direction only when he is not in a pit
		m_objSprite.move(m_direction * enemy_speed * deltaTime.asSeconds());
	}

}