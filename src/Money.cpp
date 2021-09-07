//----------------------------------include section---------------------------------
#include "Money.h"
//---------------------------------class implementation--------------------------------

int Money::m_MoneyConter = INIT; //static member initialization 

//the ctor increases the static member in order to save number of current money objects 
Money::Money(int row, int col, int index, Board& b) : ObjectsToCollect(row, col, index), m_b(b)
{
	m_MoneyConter++;
}
//the dtor decreases the static member in order to save number of current money objects 
Money::~Money()
{
	m_MoneyConter--;
}

int Money::getMoneyConter()
{
	return m_MoneyConter;
}
//when there is a collision with a game object, we double dispach
void Money::handleCollision(GameObjects& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}

void Money::handleCollision(Player& gameObject)
{
	gameObject.addMoney(MONEY * m_b.getLevel()); //add money according to level when collected
	Media::instance().playSound(S_MONEY);
	m_isDisposed = true; //mark object as removed
	gameObject.handleCollision(*this);
}