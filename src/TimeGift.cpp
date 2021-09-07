//----------------------------------include section---------------------------------
#include "TimeGift.h"
//-------------------------------functions implementation------------------------------
TimeGift::TimeGift(int row, int col, int index, Board& b) : GoodGift(row, col, index), m_b(b)
{}

//when there is a collision with a game object, we double dispach
void TimeGift::handleCollision(GameObjects& gameObject)
{
	if (&gameObject == this) return;
	gameObject.handleCollision(*this);
}

void TimeGift::handleCollision(Player& gameObject)
{
	m_isDisposed = true; // the gift was collected so we mark it as disposed
	m_b.setTimeGiftCollision(); //update the time at the board
	gameObject.handleCollision(*this);
}