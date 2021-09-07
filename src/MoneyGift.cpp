//----------------------------------include section---------------------------------
#include "MoneyGift.h"

//when there is a collision with a game object, we double dispach
void MoneyGift::handleCollision(GameObjects& gameObject)
{
	if (&gameObject == this) return;
	gameObject.handleCollision(*this);
}

void MoneyGift::handleCollision(Player& gameObject)
{
	m_isDisposed = true; // the gift was collected so we mark it as disposed
	Media::instance().playSound(S_MONEY);
	gameObject.handleCollision(*this);
}