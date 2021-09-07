
//----------------------------------include section---------------------------------
#include "Pole.h"
//-------------------------------functions implementation------------------------------

//when there is a collision with a game object, we double dispach
void Pole::handleCollision(GameObjects& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}
//when player goes on a pole
void Pole::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}