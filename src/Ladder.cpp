//----------------------------------include section---------------------------------
#include "Ladder.h"

//-------------------------------functions implementation------------------------------
void Ladder::handleCollision(GameObjects& gameObject)
{
	if (&gameObject == this) return;
	// double dispatch
	gameObject.handleCollision(*this);
}

void Ladder::handleCollision(Player& gameObject)
{
	//if the player collides with ladder, it means he's not in the air
	gameObject.setPlayerInAir(false);
	gameObject.handleCollision(*this);
}