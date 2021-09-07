
//----------------------------------include section---------------------------------
#include "LivesGift.h"

//when there is a collision with a game object, we double dispach
void LivesGift::handleCollision(GameObjects& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}

// when there is a collision with Player
void LivesGift::handleCollision(Player& gameObject)
{
	// the gift was collected so we mark it as disposed
	m_isDisposed = true;
	gameObject.handleCollision(*this);
}