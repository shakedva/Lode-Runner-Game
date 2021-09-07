//----------------------------------include section---------------------------------
#include "BadGift.h"

BadGift::BadGift(int row, int col, int index, Board& b) : Gift(row, col, index), m_b(b)
{}

// when there is a collision with GameObjects it does double dispatch
void BadGift::handleCollision(GameObjects& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}

// when there is a collision with Player
void BadGift::handleCollision(Player& gameObject)
{
	// the gift was collected so we mark it as disposed
	m_isDisposed = true; 
	// add a new enemy to the vector of enemies to the down left side of the board
	m_b.randomizeEnemy(m_b.getHeight() - 2, 1);
	gameObject.handleCollision(*this);
}